#pragma once

#include "lua_extensions.hpp"

namespace API
{
    struct Vector2 {
        double x = 0;
        double y = 0;

        Vector2(const LuaStack& args);
    };

    static int Vector2_new(lua_State* L) {
        lua_newclass<Vector2>(L);

        static auto destructor = [](lua_State* L) {
            delete lua_getself<Vector2>(L, "Vector2");
            return 0;
        };

        static auto get_len = [](lua_State* L) {
            lua_pushnumber(L, 2);
            return 1;
        };

        static auto to_string = [](lua_State* L) {
            const auto self = lua_getself<Vector2>(L, "Vector2");

            std::string result;
            result = "{ " + std::to_string(self->x) + ", " + std::to_string(self->y) + " }";

            lua_pushstring(L, result.c_str());
            return 1;
        };

        static auto index_get = [](lua_State* L) {
            const auto self = lua_getself<Vector2>(L, "Vector2");

            if (lua_isnumber(L, 2)) {
                switch (lua_tointeger(L, 2)) {
                    case 1:
                        lua_pushnumber(L, self->x);
                        break;
                    case 2:
                        lua_pushnumber(L, self->y);
                        break;
                    default:
                        lua_pushnil(L);
                }
            }
            else {
                const std::string_view key = luaL_checkstring(L, 2);
                
                if (key == "x") lua_pushnumber(L, self->x);
                else if (key == "y") lua_pushnumber(L, self->y);
                else lua_pushnil(L);
            }

            return 1;
        };

        static auto index_set = [](lua_State* L) {
            const auto self = lua_getself<Vector2>(L, "Vector2");
            double new_value = luaL_checknumber(L, 3);

            if (lua_isnumber(L, 2)) {
                switch (lua_tointeger(L, 2)) {
                    case 1:
                        self->x = new_value;
                        break;
                    case 2:
                        self->y = new_value;
                        break;
                }
            }
            else {
                const std::string_view key = luaL_checkstring(L, 2);

                if (key == "x") self->x = new_value;
                if (key == "y") self->y = new_value;
            }

            return 0;
        };

        lua_setmethods(L, "Vector2", {
            { "__gc", destructor },
            { "__len", get_len },
            { "__index", index_get },
            { "__newindex", index_set },
            { "__tostring", to_string },
        });

        return 1;
    }
}