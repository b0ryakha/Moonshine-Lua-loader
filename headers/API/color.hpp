#pragma once

#include "lua_extensions.hpp"

namespace lua
{
    static int color_new(lua_State* L) {
        int arg_count = lua_gettop(L);
        if (arg_count < 3 || arg_count > 4) return 0;

        size_t a = (arg_count == 4) ? static_cast<size_t>(round(lua_get_value<size_t>(L))) : 255;
        size_t b = static_cast<size_t>(round(lua_get_value<size_t>(L)));
        size_t g = static_cast<size_t>(round(lua_get_value<size_t>(L)));
        size_t r = static_cast<size_t>(round(lua_get_value<size_t>(L)));

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