#pragma once

#include "lua_helper.hpp"

#include <filesystem>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>
#include <optional>
#include <cstdio>
#include <curl\curl.h>

namespace fs = std::filesystem;

namespace API
{
	static int file_download(lua_State* L) {
		LuaStack args(L, "file.download");

		if (args.size() != 2)
			args.error("Incorrect number of arguments!");

		fs::path path = args.get<std::string>();
		const std::string_view url = args.get<std::string>();

		if (fs::exists(path))
			args.error("Such a file already exists!");

		if (path.empty() || !path.has_extension())
			args.error("You need to specify the name of the file with its extension!");

		CURL* curl = curl_easy_init();
		if (!curl)
			args.error("Error during CURL initialization!");

		FILE* data = fopen(path.string().c_str(), "wb");
		if (!data)
			args.error("Invalid file path!");

		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, fwrite);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, data);

		CURLcode error_id = curl_easy_perform(curl);
		if (error_id != CURLM_OK)
			args.error("Error while receiving binary code, error id: " + std::to_string(error_id));

		curl_easy_cleanup(curl);
		fclose(data);

		return 0;
	}

	static int file_exists(lua_State* L) {
		LuaStack args(L, "file.exists");

		if (args.size() != 1)
			args.error("Incorrect number of arguments!");

		fs::path path = args.get<std::string>();

		lua_pushboolean(L, fs::exists(path));
		return 1;
	}

	static int file_create(lua_State* L) {
		LuaStack args(L, "file.create");

		if (args.size() != 1)
			args.error("Incorrect number of arguments!");

		fs::path path = args.get<std::string>();
		if (fs::exists(path))
			args.error("Such a file or folder already exists!");

		if (path.has_extension()) {
			fs::create_directories(path.parent_path());

			std::ofstream ofs(path);
			ofs.close();
		}
		else {
			fs::create_directories(path);
		}

		return 0;
	}

	static int file_remove(lua_State* L) {
		LuaStack args(L, "file.remove");

		if (args.size() != 1)
			args.error("Incorrect number of arguments!");

		fs::path path = args.get<std::string>();
		if (!fs::exists(path))
			args.error("File does not exist!");

		fs::remove_all(path);

		return 0;
	}

	static int file_copy(lua_State* L) {
		LuaStack args(L, "file.copy");

		if (args.size() != 1 && args.size() != 2)
			args.error("Incorrect number of arguments!");

		fs::path path = args.get<std::string>();
		if (!fs::exists(path))
			args.error("File does not exist!");
		
		if (!path.has_extension())
			args.error("Path must be specified to the file!");

		fs::path output_path;

		if (args.size() == 2) {
			output_path = args.get<std::string>();
		}
		else {
			output_path = path;
			std::string extension = path.extension().string();

			output_path.replace_extension("");
			output_path.replace_filename(output_path.filename().string() + " (copy)" + extension);
		}

		fs::copy_file(path, output_path, fs::copy_options::overwrite_existing);

		return 0;
	}

	static int file_clear(lua_State* L) {
		LuaStack args(L, "file.clear");

		if (args.size() != 1)
			args.error("Incorrect number of arguments!");

		fs::path path = args.get<std::string>();
		if (!fs::exists(path))
			args.error("File or folder does not exist!");

		if (path.has_extension()) {
			std::ofstream file;
			file.open(path, std::ofstream::out | std::ofstream::trunc);
			file.close();
		}
		else {
			for (const auto& entry : fs::directory_iterator(path))
				fs::remove_all(entry.path());
		}

		return 0;
	}

	static int file_rename(lua_State* L) {
		LuaStack args(L, "file.rename");

		if (args.size() != 2)
			args.error("Incorrect number of arguments!");

		fs::path path = args.get<std::string>();
		if (!fs::exists(path))
			args.error("File or folder does not exist!");

		const std::string_view new_name = args.get<std::string>();

		fs::rename(path, (path.parent_path()) / new_name);

		return 0;
	}

	static int file_line_count(lua_State* L) {
		LuaStack args(L, "file.line_count");

		if (args.size() != 1)
			args.error("Incorrect number of arguments!");

		fs::path path = args.get<std::string>();
		if (!fs::exists(path))
			args.error("File does not exist!");

		if (path.has_extension())
			args.error("Path must be specified to the folder!");

		std::ifstream file(path);
		size_t length = std::count(std::istreambuf_iterator<char>(file), {}, '\n') + 1;

		file.close();

		lua_pushinteger(L, length);
		return 1;
	}

	static int file_read(lua_State* L) {
		LuaStack args(L, "file.read");

		if (args.size() != 1 && args.size() != 2)
			args.error("Incorrect number of arguments!");

		fs::path path = args.get<std::string>();
		size_t line_number = (args.size() == 2) ? args.get<size_t>() : 0;

		if (!fs::exists(path))
			args.error("File does not exist!");

		std::ifstream file(path);
		std::vector<LuaMultiValue_t> file_content;
		std::string tmp;

		while (std::getline(file, tmp, '\n'))
			file_content.emplace_back(tmp);

		if (args.size() == 1) {
			lhelper::push_table(L, file_content);
		}
		else {
			try {
				lua_pushstring(L, std::get<std::string>(file_content.at(line_number - 1)).c_str());
			}
			catch (...) {
				args.error("There is no line under this number!");
			}
		}

		file.close();
		return 1;
	}

	static int file_write(lua_State* L) {
		LuaStack args(L, "file.write");

		if (args.size() != 2 && args.size() != 3)
			args.error("Incorrect number of arguments!");

		fs::path path = args.get<std::string>();

		std::optional<LuaTable> t_content;
		std::optional<std::string> s_content;

		if (args.get_type(1) == LuaMultiValue::Table)
			t_content.emplace(args.get<LuaTable>());
		else
			s_content.emplace(args.get<std::string>());

		bool is_rewrite = (args.size() == 3) ? args.get<bool>() : false;

		if (!fs::exists(path))
			args.error("File does not exist!");

		std::stringstream buffer;
		
		if (!is_rewrite) {
			std::ifstream file_in(path);
			buffer << file_in.rdbuf();
			file_in.close();
		}

		std::ofstream file(path, std::ios::trunc);

		if (!buffer.str().empty())
			file << buffer.str() << "\n";

		if (args.get_type(1) == LuaMultiValue::Table) {
			for (size_t i = 0, size = t_content->size(); i < size; ++i)
				file << t_content->get<std::string>(std::to_string(i + 1)) << (i < size - 1 ? "\n" : "");
		}
		else {
			file << *s_content;
		}

		file.close();

		return 0;
	}

	static int file_get_list(lua_State* L) {
		LuaStack args(L, "file.get_list");

		if (args.size() != 1)
			args.error("Incorrect number of arguments!");

		fs::path path = args.get<std::string>();

		if (path.has_extension())
			args.error("Path must be specified to the folder!");

		if (!fs::exists(path))
			args.error("Folder does not exist!");

		std::vector<LuaMultiValue_t> list;

		for (const auto& entry : fs::directory_iterator(path))
			list.emplace_back(entry.path().filename().string());

		lhelper::push_table(L, list);
		return 1;
	}
}