#pragma once

#include "lua_helper.hpp"

#include <sstream>
#include <iomanip>
#include <iostream>

namespace API
{
    struct Color final : public sf::Color {
        Color(const LuaStack& args);

        static int push_to_lua(lua_State* L) {
            lhelper::new_class<Color>(L);

            static auto destructor = [](lua_State* L) {
                delete lhelper::get_object<Color>(L, "Color", 1);
                return 0;
            };

            static auto get_len = [](lua_State* L) {
                lua_pushinteger(L, 4);
                return 1;
            };

            static auto unpack = [](lua_State* L) {
                const auto self = lhelper::get_object<Color>(L, "Color", 1);

                lua_pushinteger(L, self->r);
                lua_pushinteger(L, self->g);
                lua_pushinteger(L, self->b);
                lua_pushinteger(L, self->a);
                return 4;
            };

            static auto to_hex = [](lua_State* L) {
                const auto self = lhelper::get_object<Color>(L, "Color", 1);
                size_t hex_color = (self->r << 24 | self->g << 16 | self->b << 8 | self->a);

                std::stringstream result;
                result << '#' << std::hex << std::uppercase << std::setfill('0') << std::setw(8) << hex_color;

                lua_pushstring(L, result.str().c_str());
                return 1;
            };

            static auto copy = [](lua_State* L) {
                const auto self = lhelper::get_object<Color>(L, "Color", 1);

                lhelper::push_object<Color>(L, { self->r, self->g, self->b, self->a });
                return 1;
            };

            static auto index_get = [](lua_State* L) {
                const auto self = lhelper::get_object<Color>(L, "Color", 1);

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
                else if (lua_isstring(L, 2)) {
                    const std::string_view key = luaL_checkstring(L, 2);

                    if (key == "r") lua_pushinteger(L, self->r);
                    else if (key == "g") lua_pushinteger(L, self->g);
                    else if (key == "b") lua_pushinteger(L, self->b);
                    else if (key == "a") lua_pushinteger(L, self->a);
                    else if (key == "unpack") lua_pushcfunction(L, unpack);
                    else if (key == "to_hex") lua_pushcfunction(L, to_hex);
                    else if (key == "copy") lua_pushcfunction(L, copy);
                    else lua_pushnil(L);
                }
                else {
                    lua_pushnil(L);
                }

                return 1;
            };

            static auto index_set = [](lua_State* L) {
                const auto self = lhelper::get_object<Color>(L, "Color", 1);
                int new_value = std::min(std::max(static_cast<int>(luaL_checkinteger(L, 3)), 0), 255);

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
                const auto self = lhelper::get_object<Color>(L, "Color", 1);

                std::string result;
                result = "{ " + std::to_string(self->r) + ", " + std::to_string(self->g) + ", " + std::to_string(self->b) + ", " + std::to_string(self->a) + " }";

                lua_pushstring(L, result.c_str());
                return 1;
            };

            static auto is_equal = [](lua_State* L) {
                const auto self = lhelper::get_object<Color>(L, "Color", 1);
                const auto target = lhelper::get_object<Color>(L, "Color", 2);

                lua_pushboolean(L, (
                    (self->r == target->r) &&
                    (self->g == target->g) &&
                    (self->b == target->b) &&
                    (self->a == target->a)
                ));
                return 1;
            };

            lhelper::set_methods(L, "Color", {
                { "__gc", destructor },
                { "__len", get_len },
                { "__index", index_get },
                { "__newindex", index_set },
                { "__tostring", to_string },
                { "__eq", is_equal }
            });

            return 1;
        }

        static int reg(lua_State* L) {
            LuaStack tmp(L, "");
            lua_remove(L, -static_cast<int>(tmp.size()));

            return push_to_lua(L);
        }
    };
}