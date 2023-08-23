#include "lua_extensions.hpp"

void lua_register_table(lua_State* L, std::string_view name, const std::vector<std::pair<std::string, LuaMultiValue_t>>& elements) {
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
				lua_pushstring(L, std::get<std::string>(element.second).c_str());
				break;
			case 3:
				lua_pushboolean(L, std::get<LuaBoolean>(element.second));
				break;
			default:
				lua_pushnil(L);
		}

		lua_settable(L, -3);
	}

	lua_setglobal(L, name.data());
}

void lua_pushtable(lua_State* L, const std::vector<std::pair<std::string, LuaMultiValue_t>>& elements) {
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
				lua_pushstring(L, std::get<std::string>(element.second).c_str());
				break;
			case 3:
				lua_pushboolean(L, std::get<LuaBoolean>(element.second));
				break;
			default:
				lua_pushnil(L);
		}

		lua_setfield(L, -2, element.first.c_str());
	}
}

void lua_pushtable(lua_State* L, const std::vector<LuaMultiValue_t>& elements) {
	lua_newtable(L);

	size_t index = 1;
	for (const auto& element : elements) {
		lua_pushnumber(L, index++);
		
		switch (element.index()) {
			case 0:
				lua_pushnumber(L, std::get<lua_Number>(element));
				break;
			case 1:
				lua_pushcfunction(L, std::get<lua_CFunction>(element));
				break;
			case 2:
				lua_pushstring(L, std::get<std::string>(element).c_str());
				break;
			case 3:
				lua_pushboolean(L, std::get<LuaBoolean>(element));
				break;
			default:
				lua_pushnil(L);
		}

		lua_settable(L, -3);
	}
}

void lua_setmethods(lua_State* L, std::string_view name, static const std::vector<std::pair<std::string, lua_CFunction>>& methods) {
	luaL_newmetatable(L, name.data());

	lua_pushstring(L, name.data());
	lua_setfield(L, -2, "__type");

	for (const auto& method : methods) {
		lua_pushcfunction(L, method.second);
		lua_setfield(L, -2, method.first.c_str());
	}

	lua_setmetatable(L, -2);
}