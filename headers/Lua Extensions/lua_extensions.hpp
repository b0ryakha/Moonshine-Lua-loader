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
__forceinline Class* lua_getself(lua_State* L, const std::string& class_name) {
	return *static_cast<Class**>(luaL_checkudata(L, 1, class_name.c_str()));
};

template<typename Class>
__forceinline void lua_newclass(lua_State* L) {
	*static_cast<Class**>(lua_newuserdata(L, sizeof(Class*))) = new Class(LuaStack(L));
};

__forceinline void lua_setmethods(lua_State* L, const std::string& name, static const std::vector<luaL_Reg>& methods) {
    if (luaL_newmetatable(L, name.c_str())) {
        luaL_setfuncs(L, methods.data(), 0);
        lua_pushvalue(L, -1);
        lua_setfield(L, -2, "__index");
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