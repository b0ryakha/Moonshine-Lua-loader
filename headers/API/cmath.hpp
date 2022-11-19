#pragma once

#include "lua_extensions.hpp"
#include "misc_functions.hpp"

namespace lua
{
    static int rand_int(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 2) {
            lua_pushnil(L);
            return 1;
        }

        const int min = args.get<int>(0);
        const int max = args.get<int>(1);

        lua_pushinteger(L, rand_number(min, max));
        return 1;
    }

    static int lerp(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 3) {
            lua_pushnil(L);
            return 1;
        }

        const float start = args.get<float>(0);
        const float end = args.get<float>(1);
        const float time = args.get<float>(2);

        lua_pushnumber(L, (start + time * (end - start)));
        return 1;
    }
}