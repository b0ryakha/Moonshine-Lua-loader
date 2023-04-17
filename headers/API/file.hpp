#pragma once

#include "lua_extensions.hpp"

#include <filesystem>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>
#include <cstdio>

#pragma comment(lib, "Normaliz.lib")
#pragma comment(lib, "Wldap32.lib")
#pragma comment(lib, "Crypt32.lib")
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "libcurl_a.lib")

#include <curl\curl.h>

namespace fs = std::filesystem;

namespace API
{
	static int file_download(lua_State* L) {
		LuaStack args(L);

		if (args.size() != 2)
			throw_error("[file.download] Incorrect number of arguments!");

		fs::path path = args.get<std::string>();
		std::string url = args.get<std::string>();

		if (fs::exists(path))
			throw_error("[file.download] Such a file already exists!");

		if (path.empty() || !path.has_extension())
			throw_error("[file.download] You need to specify the name of the file with its extension!");

		CURL* curl = curl_easy_init();
		if (!curl)
			throw_error("[file.download] Error during CURL initialization!");

		FILE* data = fopen(path.string().c_str(), "wb");
		if (!data)
			throw_error("[file.download] Invalid file path!");

		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, fwrite);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, data);

		CURLcode error_id = curl_easy_perform(curl);
		if (error_id != CURLM_OK)
			throw_error("[file.download] Error while receiving binary code, error id: " + std::to_string(error_id));

		curl_easy_cleanup(curl);
		fclose(data);

		return 0;
	}

	static int file_exists(lua_State* L) {
		LuaStack args(L);

		if (args.size() != 1)
			throw_error("[file.exists] Incorrect number of arguments!");

		fs::path path = args.get<std::string>();

		lua_pushboolean(L, fs::exists(path));
		return 1;
	}

	static int file_create(lua_State* L) {
		LuaStack args(L);

		if (args.size() != 1)
			throw_error("[file.create] Incorrect number of arguments!");

		fs::path path = args.get<std::string>();
		if (fs::exists(path))
			throw_error("[file.create] Such a file / folder already exists!");

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
		LuaStack args(L);

		if (args.size() != 1)
			throw_error("[file.remove] Incorrect number of arguments!");

		fs::path path = args.get<std::string>();
		if (!fs::exists(path))
			throw_error("[file.remove] The file does not exist!");

		if (path.has_extension()) {
			fs::remove(path);
		}
		else {
			fs::remove_all(path);
		}

		return 0;
	}

	static int file_copy(lua_State* L) {
		LuaStack args(L);

		if (args.size() != 1 && args.size() != 2)
			throw_error("[file.copy] Incorrect number of arguments!");

		fs::path path = args.get<std::string>();
		if (!fs::exists(path))
			throw_error("[file.copy] The file does not exist!");
		
		fs::path output_path;

		if (args.size() == 2) {
			output_path = args.get<std::string>();
		}
		else {
			output_path = path;
			fs::path extension = output_path.extension();

			output_path.replace_extension("");
			output_path.replace_filename(output_path.filename().string() + "(copy)" + extension.string());
		}

		fs::copy_file(path, output_path, fs::copy_options::overwrite_existing);

		return 0;
	}

	static int file_clear(lua_State* L) {
		LuaStack args(L);

		if (args.size() != 1)
			throw_error("[file.clear] Incorrect number of arguments!");

		fs::path path = args.get<std::string>();
		if (!fs::exists(path))
			throw_error("[file.clear] The file does not exist!");

		std::ofstream file;
		file.open(path, std::ofstream::out | std::ofstream::trunc);
		file.close();

		return 0;
	}

	static int file_rename(lua_State* L) {
		LuaStack args(L);

		if (args.size() != 2)
			throw_error("[file.rename] Incorrect number of arguments!");

		fs::path path = args.get<std::string>();
		if (!fs::exists(path))
			throw_error("[file.rename] The file does not exist!");

		std::string new_name = args.get<std::string>();

		fs::rename(path, (path.parent_path()) / new_name);

		return 0;
	}

	static int file_line_count(lua_State* L) {
		LuaStack args(L);

		if (args.size() != 1)
			throw_error("[file.line_count] Incorrect number of arguments!");

		fs::path path = args.get<std::string>();
		if (!fs::exists(path))
			throw_error("[file.line_count] The file does not exist!");

		std::ifstream file(path);
		size_t length = std::count(std::istreambuf_iterator<char>(file), {}, '\n') + 1;

		file.close();

		lua_pushinteger(L, length);
		return 1;
	}

	static int file_read(lua_State* L) {
		LuaStack args(L);

		if (args.size() != 1 && args.size() != 2)
			throw_error("[file.read] Incorrect number of arguments!");

		fs::path path = args.get<std::string>();
		size_t line_number = (args.size() == 2) ? args.get<size_t>() : 0;

		if (!fs::exists(path))
			throw_error("[file.read] The file does not exist!");

		std::ifstream file(path);
		std::vector<LuaMultiValue_t> file_content;
		std::string tmp;

		while (std::getline(file, tmp, '\n'))
			file_content.emplace_back(tmp);

		if (args.size() == 1) {
			lua_pushtable(L, file_content);
		}
		else {
			try {
				lua_pushstring(L, std::get<std::string>(file_content.at(line_number - 1)).c_str());
			}
			catch (...) {
				throw_error("[file.read] There is no line under this number!");
			}
		}

		file.close();
		return 1;
	}

	static int file_write(lua_State* L) {
		LuaStack args(L);

		if (args.size() != 2 && args.size() != 3)
			throw_error("[file.write] Incorrect number of arguments!");

		fs::path path = args.get<std::string>();

		LuaTable t_content;
		std::string s_content;

		if (args.get_type(1) == LuaMultiValue::Table) t_content = args.get<LuaTable>();
		else s_content = args.get<std::string>();

		bool is_rewrite = (args.size() == 3) ? args.get<bool>() : false;

		if (!fs::exists(path))
			throw_error("[file.write] The file does not exist!");

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
			for (size_t i = 0, size = t_content.size(); i < size; ++i)
				file << t_content.get<std::string>(std::to_string(i + 1)) << (i < size - 1 ? "\n" : "");
		}
		else {
			file << s_content;
		}

		file.close();

		return 0;
	}

	static int file_get_list(lua_State* L) {
		LuaStack args(L);

		if (args.size() != 1)
			throw_error("[file.get_list] Incorrect number of arguments!");

		fs::path path = args.get<std::string>();

		if (path.has_extension())
			throw_error("[file.get_list] The path must be specified to the folder!");

		if (!fs::exists(path))
			throw_error("[file.get_list] The folder does not exist!");

		std::vector<LuaMultiValue_t> list;

		for (const auto& entry : fs::directory_iterator(path))
			list.emplace_back(entry.path().filename().string());

		lua_pushtable(L, list);
		return 1;
	}
}