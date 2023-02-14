#pragma once

#include "lua_extensions.hpp"

#include <filesystem>
namespace fs = std::filesystem;

extern double main_time;

namespace API
{
	static int get_frametime(lua_State* L) {
		lua_pushnumber(L, main_time);
		return 1;
	}

	static int get_executable_path(lua_State* L) {
		lua_pushstring(L, fs::current_path().generic_string().c_str());
		return 1;
	}
}