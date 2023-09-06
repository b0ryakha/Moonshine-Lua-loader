#pragma once

#include "lua_helper.hpp"

#include <sstream>

namespace API
{
    struct Vector2 final : public sf::Vector2f {
        Vector2(const LuaStack& args);

        static int push_to_lua(lua_State* L) {
            lhelper::new_class<Vector2>(L);

            static auto destructor = [](lua_State* L) {
                delete lhelper::get_object<Vector2>(L, "Vector2", 1);
                return 0;
            };

            static auto get_len = [](lua_State* L) {
                lua_pushinteger(L, 2);
                return 1;
            };

            static auto copy = [](lua_State* L) {
                const auto self = lhelper::get_object<Vector2>(L, "Vector2", 1);

                lhelper::push_object<Vector2>(L, { self->x, self->y });
                return 1;
            };

            static auto index_get = [](lua_State* L) {
                const auto self = lhelper::get_object<Vector2>(L, "Vector2", 1);

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
                const auto self = lhelper::get_object<Vector2>(L, "Vector2", 1);
                double new_value = luaL_checknumber(L, 3);

                if (lua_isnumber(L, 2)) {
                    switch (lua_tointeger(L, 2)) {
                        case 1:
                            self->x = new_value;
                            break;
                        case 2:
                            self->y = new_value;
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
                const auto self = lhelper::get_object<Vector2>(L, "Vector2", 1);

                std::stringstream result;
                result << "{ " << self->x << ", " << self->y << " }";

                lua_pushstring(L, result.str().c_str());
                return 1;
            };

            static auto is_equal = [](lua_State* L) {
                const auto self = lhelper::get_object<Vector2>(L, "Vector2", 1);
                const auto target = lhelper::get_object<Vector2>(L, "Vector2", 2);

                lua_pushboolean(L, ((self->x == target->x) && (self->y == target->y)));
                return 1;
            };

            static auto add = [](lua_State* L) {
                const auto self = lhelper::get_object<Vector2>(L, "Vector2", 1);

                if (lua_isnumber(L, 2)) {
                    float number = lua_tonumber(L, 2);
                    lhelper::push_object<Vector2>(L, { self->x + number, self->y + number });
                }
                else {
                    const auto target = lhelper::get_object<Vector2>(L, "Vector2", 2);
                    lhelper::push_object<Vector2>(L, { self->x + target->x, self->y + target->y });
                }

                return 1;
            };

            static auto sub = [](lua_State* L) {
                const auto self = lhelper::get_object<Vector2>(L, "Vector2", 1);

                if (lua_isnumber(L, 2)) {
                    float number = lua_tonumber(L, 2);
                    lhelper::push_object<Vector2>(L, { self->x - number, self->y - number });
                }
                else {
                    const auto target = lhelper::get_object<Vector2>(L, "Vector2", 2);
                    lhelper::push_object<Vector2>(L, { self->x - target->x, self->y - target->y });
                }

                return 1;
            };

            static auto mul = [](lua_State* L) {
                const auto self = lhelper::get_object<Vector2>(L, "Vector2", 1);
                
                if (lua_isnumber(L, 2)) {
                    float number = lua_tonumber(L, 2);
                    lhelper::push_object<Vector2>(L, { self->x * number, self->y * number });
                }
                else {
                    const auto target = lhelper::get_object<Vector2>(L, "Vector2", 2);
                    lhelper::push_object<Vector2>(L, { self->x * target->x, self->y * target->y });
                }

                return 1;
            };

            static auto div = [](lua_State* L) {
                const auto self = lhelper::get_object<Vector2>(L, "Vector2", 1);

                if (lua_isnumber(L, 2)) {
                    float number = lua_tonumber(L, 2);

                    if (number == 0)
                        throw_error("[Vector2:div] Division by zero!");

                    lhelper::push_object<Vector2>(L, { self->x / number, self->y / number });
                }
                else {
                    const auto target = lhelper::get_object<Vector2>(L, "Vector2", 2);

                    if (target->x == 0 || target->y == 0)
                        throw_error("[Vector2:div] Division by zero!");

                    lhelper::push_object<Vector2>(L, { self->x / target->x, self->y / target->y });
                }

                return 1;
            };

            lhelper::set_methods(L, "Vector2", {
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

        static int reg(lua_State* L) {
            LuaStack tmp(L, "");
            lua_remove(L, -static_cast<int>(tmp.size()));

            return push_to_lua(L);
        }
    };
}