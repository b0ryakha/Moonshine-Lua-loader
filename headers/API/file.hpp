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

		std::string path = args.get<std::string>();
		std::string url = args.get<std::string>();

		if (fs::exists(path))
			throw_error("[file.download] Such a file already exists!");

		if (path.empty() || path.find('.') == std::string::npos)
			throw_error("[file.download] You need to specify the name of the file with its extension!");

		CURL* curl = curl_easy_init();
		if (!curl)
			throw_error("[file.download] Error during CURL initialization!");

		FILE* data = fopen(path.c_str(), "wb");
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
			throw_error("[file.create] Such a file already exists!");

		fs::create_directories(path.parent_path());

		std::ofstream ofs(path);
		ofs.close();

		return 0;
	}

	static int file_remove(lua_State* L) {
		LuaStack args(L);

		if (args.size() != 1)
			throw_error("[file.remove] Incorrect number of arguments!");

		fs::path path = args.get<std::string>();
		if (!fs::exists(path))
			throw_error("[file.remove] The file does not exist!");

		fs::remove(path);

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
			throw_error("[file.length] Incorrect number of arguments!");

		fs::path path = args.get<std::string>();
		if (!fs::exists(path))
			throw_error("[file.length] The file does not exist!");

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
		std::vector<LuaMultiValue> file_content;
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
		LuaTable content = args.get<LuaTable>();
		bool is_rewrite = (args.size() == 3) ? args.get<bool>() : false;

		if (!fs::exists(path))
			throw_error("[file.write] The file does not exist!");

		if (is_rewrite) {
			std::ofstream file;
			file.open(path, std::ofstream::out | std::ofstream::trunc);
			file.close();
		}

		std::ofstream file(path);
		size_t size = content.size();

		for (size_t i = 0; i < size; ++i)
			file << content.get<std::string>() << (i < size - 1 ? "\n" : "");

		file.close();

		return 0;
	}
}