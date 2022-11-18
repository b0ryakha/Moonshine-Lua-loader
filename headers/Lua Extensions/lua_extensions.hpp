#pragma once

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

#include "misc_functions.hpp"
#include "LuaStack.hpp"

#include "lua.hpp"
extern "C" {
	#pragma comment(lib, "lua54.lib")
}

__forceinline void lua_register_table(lua_State* L, const std::string& name, const std::vector<std::pair<std::string, LuaMultiValue>>& elements) {
	lua_newtable(L);

	for (const auto& element : elements) {
		lua_pushstring(L, element.first.c_str());

		switch (element.second.index()) {
			case 0:
				lua_pushnumber(L, std::get<lua_Number>(element.second));
				break;
			case 1:
				lua_pushcfunction(L, std::get<lua_CFunction>(element.second));
				break;
			case 2:
				lua_pushstring(L, (std::get<std::string>(element.second)).c_str());
				break;
			case 3:
				lua_pushboolean(L, std::get<LuaBoolean>(element.second).state);
				break;
			default:
				lua_pushnil(L);
		}

		lua_settable(L, -3);
	}

	lua_setglobal(L, name.c_str());
}

__forceinline void lua_pushtable(lua_State* L, const std::vector<std::pair<std::string, LuaMultiValue>>& elements) {
	lua_newtable(L);

	for (const auto& element : elements) {
		switch (element.second.index()) {
			case 0:
				lua_pushnumber(L, std::get<lua_Number>(element.second));
				break;
			case 1:
				lua_pushcfunction(L, std::get<lua_CFunction>(element.second));
				break;
			case 2:
				lua_pushstring(L, (std::get<std::string>(element.second)).c_str());
				break;
			case 3:
				lua_pushboolean(L, std::get<LuaBoolean>(element.second).state);
				break;
			default:
				lua_pushnil(L);
		}

		lua_setfield(L, -2, element.first.c_str());
	}
}