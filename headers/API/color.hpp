#pragma once

#include "lua_extensions.hpp"

/*__forceinline sf::Color lua_get_color(lua_State* L, int arg_count) {
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
}*/

namespace lua
{
    static int color_new(lua_State* L) {
        LuaStack args(L);
        if (args.size() < 3 || args.size() > 4) return 0;

        size_t r = static_cast<size_t>(round(args.get<size_t>(0)));
        size_t g = static_cast<size_t>(round(args.get<size_t>(1)));
        size_t b = static_cast<size_t>(round(args.get<size_t>(2)));
        size_t a = (args.size() == 4) ? static_cast<size_t>(round(args.get<size_t>(3))) : 255;

        if (r > 255) r = 255;
        if (g > 255) g = 255;
        if (b > 255) b = 255;
        if (a > 255) a = 255;

        lua_newtable(L);
        lua_pushinteger(L, r); lua_setfield(L, -2, "r");
        lua_pushinteger(L, g); lua_setfield(L, -2, "g");
        lua_pushinteger(L, b); lua_setfield(L, -2, "b");
        lua_pushinteger(L, a); lua_setfield(L, -2, "a");

        return 1;
    }
}