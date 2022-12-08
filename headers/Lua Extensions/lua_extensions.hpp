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

void lua_register_table(lua_State* L, const std::string& name, const std::vector<std::pair<std::string, LuaMultiValue>>& elements);

void lua_pushtable(lua_State* L, const std::vector<std::pair<std::string, LuaMultiValue>>& elements);
void lua_pushtable(lua_State* L, const std::vector<LuaMultiValue>& elements);

__forceinline sf::Color lua_getcolor(const LuaStack& stack, int index) {
	LuaTable color = stack.get<LuaTable>(index);
	return sf::Color(color.get<int>("r"), color.get<int>("g"), color.get<int>("b"), color.get<int>("a"));
}

__forceinline sf::Color lua_getcolor(const LuaStack& stack) {
	LuaTable color = stack.get<LuaTable>();
	return sf::Color(color.get<int>("r"), color.get<int>("g"), color.get<int>("b"), color.get<int>("a"));
}