#pragma once

#include "lua_extensions.hpp"

namespace lua
{
    static int color_new(lua_State* L) {
        LuaStack args(L);

        if (args.size() < 3 || args.size() > 4) {
            lua_pushnil(L);
            return 1;
        }

        size_t r = args.get<size_t>(0);
        size_t g = args.get<size_t>(1);
        size_t b = args.get<size_t>(2);
        size_t a = (args.size() == 4) ? args.get<size_t>(3) : 255;
        
        if (r > 255) r = 255;
        if (g > 255) g = 255;
        if (b > 255) b = 255;
        if (a > 255) a = 255;

        lua_pushtable(L, {
            std::make_pair("r", r),
            std::make_pair("g", g),
            std::make_pair("b", b),
            std::make_pair("a", a),
        });

        return 1;
    }
}