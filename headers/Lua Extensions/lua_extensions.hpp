#pragma once

#include <vector>
#include <string>

#include "misc_functions.hpp"
#include "LuaStack.hpp"

void lua_register_table(lua_State* L, std::string_view name, const std::vector<std::pair<std::string, LuaMultiValue_t>>& elements);

template<typename Class>
__forceinline void lua_register_class(lua_State* L, std::string_view name) {
	lua_register_table(L, name, { std::make_pair("new", Class::reg) });
}

void lua_pushtable(lua_State* L, const std::vector<std::pair<std::string, LuaMultiValue_t>>& elements);
void lua_pushtable(lua_State* L, const std::vector<LuaMultiValue_t>& elements);

template<typename Class>
__forceinline void lua_newclass(lua_State* L) {
	*static_cast<Class**>(lua_newuserdata(L, sizeof(Class*))) = new Class(std::move(LuaStack(L, "")));
};

template<typename Class>
__forceinline Class* lua_get_object(lua_State* L, std::string_view class_name, size_t index) {
	return *static_cast<Class**>(luaL_checkudata(L, index, class_name.data()));
};

template<typename Class>
void lua_push_object(lua_State* L, const std::vector<LuaMultiValue_t>& args) {
	LuaStack old_stack(L, "");

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
				lua_pushboolean(L, std::get<LuaBoolean>(arg));
				break;
			default:
				lua_pushnil(L);
		}
	}

	Class::push_to_lua(L);
}

void lua_setmethods(lua_State* L, std::string_view name, static const std::vector<std::pair<std::string, lua_CFunction>>& methods);