#pragma once

#include "lua_extensions.hpp"

namespace API
{
    struct Color {
        size_t r = 0;
        size_t g = 0;
        size_t b = 0;
        size_t a = 255;

        Color(const LuaStack& args);
        operator sf::Color() const { return sf::Color(r, g, b, a); };
    };

    static int Color_new(lua_State* L) {
        lua_newclass<Color>(L);

        static auto destructor = [](lua_State* L) {
            delete lua_get_object<Color>(L, "Color", 1);
            return 0;
        };

        static auto get_len = [](lua_State* L) {
            lua_pushnumber(L, 4);
            return 1;
        };

        static auto unpack = [](lua_State* L) {
            const auto self = lua_get_object<Color>(L, "Color", 1);

            lua_pushinteger(L, self->r);
            lua_pushinteger(L, self->g);
            lua_pushinteger(L, self->b);
            lua_pushinteger(L, self->a);
            return 4;
        };

        static auto to_hex = [](lua_State* L) {
            const auto self = lua_get_object<Color>(L, "Color", 1);
            std::stringstream ss;

            ss << '#' << std::hex << (self->r << 24 | self->g << 16 | self->b << 8 | self->a);

            lua_pushstring(L, ss.str().c_str());
            return 1;
        };

        static auto index_get = [](lua_State* L) {
            const auto self = lua_get_object<Color>(L, "Color", 1);

            if (lua_isnumber(L, 2)) {
                switch (lua_tointeger(L, 2)) {
                    case 1:
                        lua_pushinteger(L, self->r);
                        break;
                    case 2:
                        lua_pushinteger(L, self->g);
                        break;
                    case 3:
                        lua_pushinteger(L, self->b);
                        break;
                    case 4:
                        lua_pushinteger(L, self->a);
                        break;
                    default:
                        lua_pushnil(L);
                }
            }
            else {
                const std::string_view key = luaL_checkstring(L, 2);

                if (key == "r") lua_pushinteger(L, self->r);
                else if (key == "g") lua_pushinteger(L, self->g);
                else if (key == "b") lua_pushinteger(L, self->b);
                else if (key == "a") lua_pushinteger(L, self->a);
                else if (key == "unpack") lua_pushcfunction(L, unpack);
                else if (key == "to_hex") lua_pushcfunction(L, to_hex);
                else lua_pushnil(L);
            }

            return 1;
        };

        static auto index_set = [](lua_State* L) {
            const auto self = lua_get_object<Color>(L, "Color", 1);
            double new_value = luaL_checknumber(L, 3);

            if (lua_isnumber(L, 2)) {
                switch (lua_tointeger(L, 2)) {
                    case 1:
                        self->r = new_value;
                        break;
                    case 2:
                        self->g = new_value;
                        break;
                    case 3:
                        self->b = new_value;
                        break;
                    case 4:
                        self->a = new_value;
                        break;
                }
            }
            else {
                const std::string_view key = luaL_checkstring(L, 2);

                if (key == "r") self->r = new_value;
                if (key == "g") self->g = new_value;
                if (key == "b") self->b = new_value;
                if (key == "a") self->a = new_value;
            }

            return 0;
        };

        static auto to_string = [](lua_State* L) {
            const auto self = lua_get_object<Color>(L, "Color", 1);

            std::string result;
            result = "{ " + std::to_string(self->r) + ", " + std::to_string(self->g) + ", " + std::to_string(self->b) + ", " + std::to_string(self->a) + " }";

            lua_pushstring(L, result.c_str());
            return 1;
        };

        static auto is_equal = [](lua_State* L) {
            const auto self = lua_get_object<Color>(L, "Color", 1);
            const auto target = lua_get_object<Color>(L, "Color", 2);

            lua_pushboolean(L, ((self->r == target->r) && (self->g == target->g) && (self->b == target->b) && (self->a == target->a)));
            return 1;
        };

        lua_setmethods(L, "Color", {
            { "__gc", destructor },
            { "__len", get_len },
            { "__index", index_get },
            { "__newindex", index_set },
            { "__tostring", to_string },
            { "__eq", is_equal }
        });

        return 1;
    }
}