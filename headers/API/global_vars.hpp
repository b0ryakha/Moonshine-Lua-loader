#pragma once

#include "lua_extensions.hpp"

#include <mutex>

inline double main_time = 0;
inline std::mutex time_m;

namespace lua
{
	static int get_frametime(lua_State* L) {
		lua_pushnumber(L, main_time);
		return 1;
	}
}