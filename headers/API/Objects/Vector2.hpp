#pragma once

#include "lua_extensions.hpp"

namespace API
{
    struct Vector2 final {
        double x = 0;
        double y = 0;

        Vector2(const LuaStack& args);
        operator sf::Vector2f() const;
    };

    static int Vector2_new(lua_State* L) {
        lua_newclass<Vector2>(L);

        static auto destructor = [](lua_State* L) {
            delete lua_get_object<Vector2>(L, "Vector2", 1);
            return 0;
        };

        static auto get_len = [](lua_State* L) {
            lua_pushinteger(L, 2);
            return 1;
        };

        static auto copy = [](lua_State* L) {
            const auto self = lua_get_object<Vector2>(L, "Vector2", 1);

            lua_push_object<Vector2_new>(L, { self->x, self->y });
            return 1;
        };

        static auto index_get = [](lua_State* L) {
            const auto self = lua_get_object<Vector2>(L, "Vector2", 1);

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
            else if (lua_isstring(L, 2)) {
                const std::string_view key = luaL_checkstring(L, 2);
                
                if (key == "x") lua_pushnumber(L, self->x);
                else if (key == "y") lua_pushnumber(L, self->y);
                else if (key == "copy") lua_pushcfunction(L, copy);
                else lua_pushnil(L);
            }
            else {
                lua_pushnil(L);
            }

            return 1;
        };

        static auto index_set = [](lua_State* L) {
            const auto self = lua_get_object<Vector2>(L, "Vector2", 1);
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

        static auto to_string = [](lua_State* L) {
            const auto self = lua_get_object<Vector2>(L, "Vector2", 1);

            std::string result;
            result = "{ " + number_to_str(self->x) + ", " + number_to_str(self->y) + " }";

            lua_pushstring(L, result.c_str());
            return 1;
        };

        static auto is_equal = [](lua_State* L) {
            const auto self = lua_get_object<Vector2>(L, "Vector2", 1);
            const auto target = lua_get_object<Vector2>(L, "Vector2", 2);

            lua_pushboolean(L, ((self->x == target->x) && (self->y == target->y)));
            return 1;
        };

        static auto add = [](lua_State* L) {
            const auto self = lua_get_object<Vector2>(L, "Vector2", 1);
            const auto target = lua_get_object<Vector2>(L, "Vector2", 2);

            lua_push_object<Vector2_new>(L, { self->x + target->x, self->y + target->y });
            return 1;
        };

        static auto sub = [](lua_State* L) {
            const auto self = lua_get_object<Vector2>(L, "Vector2", 1);
            const auto target = lua_get_object<Vector2>(L, "Vector2", 2);

            lua_push_object<Vector2_new>(L, { self->x - target->x, self->y - target->y });
            return 1;
        };

        static auto mul = [](lua_State* L) {
            const auto self = lua_get_object<Vector2>(L, "Vector2", 1);
            const auto target = lua_get_object<Vector2>(L, "Vector2", 2);

            lua_push_object<Vector2_new>(L, { self->x * target->x, self->y * target->y });
            return 1;
        };

        static auto div = [](lua_State* L) {
            const auto self = lua_get_object<Vector2>(L, "Vector2", 1);
            const auto target = lua_get_object<Vector2>(L, "Vector2", 2);

            if (target->x == 0 || target->y == 0)
                throw_error("[Vector2 div] Division by zero!");

            lua_push_object<Vector2_new>(L, { self->x / target->x, self->y / target->y });
            return 1;
        };

        lua_setmethods(L, "Vector2", {
            { "__gc", destructor },
            { "__len", get_len },
            { "__index", index_get },
            { "__newindex", index_set },
            { "__tostring", to_string },
            { "__eq", is_equal },
            { "__add", add },
            { "__sub", sub },
            { "__mul", mul },
            { "__div", div }
        });

        return 1;
    }

    static int Vector2_reg(lua_State* L) {
        LuaStack tmp(L);
        lua_remove(L, -static_cast<int>(tmp.size()));

        return Vector2_new(L);
    }
}