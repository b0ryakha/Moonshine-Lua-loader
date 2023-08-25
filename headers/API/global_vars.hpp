#pragma once

#include <filesystem>
namespace fs = std::filesystem;

namespace API
{
	static int get_executable_path(lua_State* L) {
		lua_pushstring(L, fs::current_path().generic_string().c_str());
		return 1;
	}
}