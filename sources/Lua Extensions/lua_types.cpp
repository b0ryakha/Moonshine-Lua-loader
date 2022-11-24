#include "lua_types.hpp"

LuaTable::LuaTable(lua_State* lua_state, int index) {
    lua_pushvalue(lua_state, index);
    lua_pushnil(lua_state);

    while (lua_next(lua_state, -2)) {
        lua_pushvalue(lua_state, -2);

        const std::string_view key = static_cast<std::string_view>(lua_tostring(lua_state, -1));

        switch (lua_type(lua_state, -2)) {
            case LUA_TSTRING:
                elements[key] = std::move(static_cast<std::string>(lua_tostring(lua_state, -2)));
                break;
            case LUA_TBOOLEAN:
                elements[key] = std::move(LuaBoolean(lua_toboolean(lua_state, -2)));
                break;
            case LUA_TNUMBER:
                elements[key] = std::move(static_cast<lua_Number>(lua_tonumber(lua_state, -2)));
                break;
            case LUA_TFUNCTION:
                elements[key] = std::move(static_cast<lua_CFunction>(lua_tocfunction(lua_state, -2)));
                break;
            default:
                elements[key] = std::move(LuaNil());
        }

        lua_pop(lua_state, 2);
    }

    lua_pop(lua_state, 1);
}