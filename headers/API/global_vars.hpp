#pragma once

#include "lua_extensions.hpp"

extern double main_time;

namespace lua
{
	static int get_frametime(lua_State* L) {
		lua_pushnumber(L, main_time);
		return 1;
	}
}