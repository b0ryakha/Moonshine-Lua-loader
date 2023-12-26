#pragma once

#include <vector>
#include <string>

#include "misc_functions.hpp"
#include "LuaStack.hpp"

namespace lhelper
{
	void register_table(lua_State* L, std::string_view name, const std::vector<std::pair<std::string, LuaMultiValue_t>>& elements);
	void push_table(lua_State* L, const std::vector<std::pair<std::string, LuaMultiValue_t>>& elements);
	void push_table(lua_State* L, const std::vector<LuaMultiValue_t>& elements);
	void set_methods(lua_State* L, std::string_view name, const std::vector<std::pair<std::string, lua_CFunction>>& methods);

	template<typename APIStruct>
	void register_class(lua_State* L, std::string_view name) {
		lhelper::register_table(L, name, { std::make_pair("new", APIStruct::reg) });
	}

	template<typename APIStruct>
	void new_class(lua_State* L) {
		*static_cast<APIStruct**>(lua_newuserdata(L, sizeof(APIStruct*))) = new APIStruct(std::move(LuaStack(L, "")));
	};

	template<typename APIStruct>
	APIStruct* get_object(lua_State* L, std::string_view class_name, size_t index) {
		return *static_cast<APIStruct**>(luaL_checkudata(L, index, class_name.data()));
	};

	template<typename APIStruct>
	void push_object(lua_State* L, const std::vector<LuaMultiValue_t>& args) {
		LuaStack old_stack(L, "LuaStack:push_object");

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

		APIStruct::push_to_lua(L);
	}
}