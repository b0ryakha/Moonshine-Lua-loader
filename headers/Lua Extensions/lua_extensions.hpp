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

template<typename Class>
__forceinline Class* lua_getclass(lua_State* L, const std::string& class_name, size_t index) {
	return *static_cast<Class**>(luaL_checkudata(L, index, class_name.c_str()));
};

template<typename Class>
__forceinline Class* lua_getself(lua_State* L, const std::string& class_name) {
	return lua_getclass<Class>(L, class_name, 1);
};

template<typename Class>
__forceinline void lua_newclass(lua_State* L) {
	*static_cast<Class**>(lua_newuserdata(L, sizeof(Class*))) = new Class(std::move(LuaStack(L)));
};

template<lua_CFunction constructor>
void lua_push_object(lua_State* L, const std::vector<LuaMultiValue>& args) {
	LuaStack old_stack(L);

	if (!old_stack.empty())
		lua_pop(L, static_cast<int>(old_stack.size()));

	for (const auto& arg : args) {
		switch (arg.index()) {
			case 0:
				lua_pushnumber(L, std::get<lua_Number>(arg));
				break;
			case 1:
				lua_pushcfunction(L, std::get<lua_CFunction>(arg));
				break;
			case 2:
				lua_pushstring(L, std::get<std::string>(arg).c_str());
				break;
			case 3:
				lua_pushboolean(L, std::get<LuaBoolean>(arg).state);
				break;
			default:
				lua_pushnil(L);
		}
	}

	constructor(L);
}

__forceinline void lua_setmethods(lua_State* L, const std::string& name, static const std::vector<std::pair<std::string, lua_CFunction>>& methods) {
    if (luaL_newmetatable(L, name.c_str())) {
		for (const auto& function : methods) {
			lua_pushcfunction(L, function.second);
			lua_setfield(L, -2, function.first.c_str());
		}

		lua_setmetatable(L, -2);
    }
}

__forceinline sf::Color lua_getcolor(const LuaStack& stack, int index) {
	LuaTable color = stack.get<LuaTable>(index);
	return sf::Color(color.get<int>("r"), color.get<int>("g"), color.get<int>("b"), color.get<int>("a"));
}

__forceinline sf::Color lua_getcolor(const LuaStack& stack) {
	LuaTable color = stack.get<LuaTable>();
	return sf::Color(color.get<int>("r"), color.get<int>("g"), color.get<int>("b"), color.get<int>("a"));
}