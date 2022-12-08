#pragma once

#include "lua_extensions.hpp"
#include "misc_functions.hpp"

namespace API
{
    static int rand_int(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 2) {
            lua_pushnil(L);
            return 1;
        }

        const int min = args.get<int>();
        const int max = args.get<int>();

        lua_pushinteger(L, rand_number(min, max));
        return 1;
    }

    static int lerp(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 3) {
            lua_pushnil(L);
            return 1;
        }

        const float start = args.get<float>();
        const float end = args.get<float>();
        const float time = args.get<float>();

        lua_pushnumber(L, (start + time * (end - start)));
        return 1;
    }

    static int clamp(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 3) {
            lua_pushnil(L);
            return 1;
        }

        const float number = args.get<float>();
        const float lower = args.get<float>();
        const float upper = args.get<float>();
        
        lua_pushnumber(L, std::clamp(number, lower, upper));
        return 1;
    }
}