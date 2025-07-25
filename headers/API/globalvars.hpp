#pragma once
#include "lua_helper.hpp"

#include <filesystem>
namespace fs = std::filesystem;

inline std::vector<LuaMultiValue_t> args;

namespace API
{
	static int get_executable_path(lua_State* L) {
		lua_pushstring(L, fs::current_path().generic_string().c_str());
		return 1;
	}

	// TODO: just improve _G.arg table.
	static int get_args(lua_State* L) {
		lhelper::push_table(L, args);
		return 1;
	}

	static int get_os_name(lua_State* L) {
		#ifdef _WIN32
		lua_pushstring(L, "Windows");
		#elif defined(__linux__)
		lua_pushstring(L, "Linux");
		#else
		lua_pushstring(L, "Unknown");
		#endif

		return 1;
	}
}