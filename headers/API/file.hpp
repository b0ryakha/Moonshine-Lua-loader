#pragma once

#include "lua_extensions.hpp"

#include <filesystem>
#include <fstream>
#include <vector>
#include <string>

namespace fs = std::filesystem;

namespace API
{
	static int file_read(lua_State* L) {
		LuaStack args(L);

		if (args.size() != 1 && args.size() != 2)
			throw_error("[file.read] Incorrect number of arguments!");

		fs::path path = args.get<std::string>();
		size_t line_number = (args.size() == 2) ? args.get<size_t>() : 0;

		if (!fs::exists(path))
			throw_error("[file.read] The file does not exist!");

		std::ifstream file(path);
		std::vector<std::string> file_content;
		std::string tmp;

		while (std::getline(file, tmp, '\n'))
			file_content.emplace_back(tmp);

		if (args.size() == 1) {
			lua_pushtable(L, std::vector<LuaMultiValue>(file_content.begin(), file_content.end()));
		}
		else {
			try {
				lua_pushstring(L, file_content.at(line_number - 1).c_str());
			}
			catch (...) {
				throw_error("[file.read] There is no line under this number!");
			}
		}

		file.close();
		return 1;
	}
}