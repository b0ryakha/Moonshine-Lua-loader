#pragma once

#include <vector>
#include <string>
#include <variant>
#include <SFML/Graphics.hpp>

#include "lua.hpp"

extern "C" {
	#pragma comment(lib, "lua54.lib")
}

__forceinline void lua_register_table(lua_State* L, const std::string& name, const std::vector<std::pair<std::string, std::variant<lua_Number, lua_CFunction, std::string>>> elements) {
	lua_newtable(L);
	for (auto& element : elements) {
		lua_pushstring(L, element.first.c_str());
		switch (element.second.index()) {
		case 0: {
			lua_pushnumber(L, std::get<lua_Number>(element.second));
			break;
		}
		case 1: {
			lua_pushcfunction(L, std::get<lua_CFunction>(element.second));
			break;
		}
		case 2: {
			lua_pushstring(L, (std::get<std::string>(element.second)).c_str());
			break;
		}
		}
		lua_settable(L, -3);
	}

	lua_setglobal(L, name.c_str());
}

__forceinline sf::Color lua_get_color(lua_State* L, int arg_count) {
	lua_settop(L, arg_count);
	luaL_checktype(L, arg_count, LUA_TTABLE);
	lua_getfield(L, arg_count, "r");
	lua_getfield(L, arg_count, "g");
	lua_getfield(L, arg_count, "b");
	lua_getfield(L, arg_count, "a");

	int r = static_cast<int>(luaL_checkinteger(L, -4));
	int g = static_cast<int>(luaL_checkinteger(L, -3));
	int b = static_cast<int>(luaL_checkinteger(L, -2));
	int a = static_cast<int>(luaL_checkinteger(L, -1));

	return sf::Color(r, g, b, a);
}

template<typename T>
__forceinline T lua_get_value(lua_State* L) { throw "Unknown Type!"; }

template<>
__forceinline int lua_get_value<int>(lua_State* L) {
	int result = static_cast<int>(luaL_checknumber(L, lua_gettop(L)));
	lua_pop(L, 1);

	return result;
}

template<>
__forceinline size_t lua_get_value<size_t>(lua_State* L) {
	int result = static_cast<int>(luaL_checknumber(L, lua_gettop(L)));
	if (result < 0) result = 0;

	lua_pop(L, 1);

	return static_cast<size_t>(result);
}

template<>
__forceinline float lua_get_value<float>(lua_State* L) {
	float result = static_cast<float>(luaL_checknumber(L, lua_gettop(L)));
	lua_pop(L, 1);

	return result;
}

template<>
__forceinline std::string lua_get_value<std::string>(lua_State* L) {
	std::string result = static_cast<std::string>(luaL_checkstring(L, lua_gettop(L)));
	lua_pop(L, 1);

	return result;
}

template<>
__forceinline bool lua_get_value<bool>(lua_State* L) {
	if (!lua_isboolean(L, lua_gettop(L)))
		throw "Incorrect type! Expected bool.";

	bool result = static_cast<bool>(lua_toboolean(L, lua_gettop(L)));
	lua_pop(L, 1);

	return result;
}

template<>
__forceinline double lua_get_value<double>(lua_State* L) {
	double result = static_cast<double>(luaL_checknumber(L, lua_gettop(L)));
	lua_pop(L, 1);

	return result;
}