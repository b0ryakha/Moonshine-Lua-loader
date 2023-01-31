#pragma once

#include "lua_extensions.hpp"

#include "API/Objects/Vector2.hpp"

#include <sstream>

namespace API
{
    struct View final : public sf::View {
        View(const LuaStack& args);

        static int push_to_lua(lua_State* L) {
            lua_newclass<View>(L);

            static auto destructor = [](lua_State* L) {
                delete lua_get_object<View>(L, "View", 1);
                return 0;
            };

            static auto active = [](lua_State* L) {
                auto self = lua_get_object<View>(L, "View", 1);
                window.setView(*self);

                return 0;
            };

            static auto set_port = [](lua_State* L) {
                auto self = lua_get_object<View>(L, "View", 1);
                float x = luaL_checknumber(L, 2);
                float y = luaL_checknumber(L, 3);
                float w = luaL_checknumber(L, 4);
                float h = luaL_checknumber(L, 5);

                self->setViewport(sf::FloatRect(
                    x / window.getSize().x,
                    y / window.getSize().y,
                    w / window.getSize().x,
                    h / window.getSize().y
                ));

                return 0;
            };

            static auto set_center = [](lua_State* L) {
                auto self = lua_get_object<View>(L, "View", 1);
                float x = luaL_checknumber(L, 2);
                float y = luaL_checknumber(L, 3);

                self->setCenter(x, y);

                return 0;
            };

            static auto set_size = [](lua_State* L) {
                auto self = lua_get_object<View>(L, "View", 1);
                float w = luaL_checknumber(L, 2);
                float h = luaL_checknumber(L, 3);

                self->setSize(w, h);

                return 0;
            };

            static auto get_size = [](lua_State* L) {
                auto self = lua_get_object<View>(L, "View", 1);

                lua_push_object<Vector2>(L, {
                    self->getSize().x,
                    self->getSize().y
                });
                return 1;
            };

            static auto set_zoom = [](lua_State* L) {
                auto self = lua_get_object<View>(L, "View", 1);
                float zoom_factor = luaL_checknumber(L, 2);

                self->zoom((100.f - zoom_factor) / 100.f);

                return 0;
            };

            static auto set_rotation = [](lua_State* L) {
                auto self = lua_get_object<View>(L, "View", 1);
                float angle = luaL_checknumber(L, 2);

                self->setRotation(angle);

                return 0;
            };

            static auto get_rotation = [](lua_State* L) {
                auto self = lua_get_object<View>(L, "View", 1);

                lua_pushnumber(L, self->getRotation());
                return 0;
            };

            static auto copy = [](lua_State* L) {
                const auto self = lua_get_object<View>(L, "View", 1);
                sf::Vector2f center_pos = self->getCenter();
                sf::Vector2f size = self->getSize();

                lua_push_object<View>(L, { center_pos.x - size.x / 2, center_pos.y - size.y / 2, size.x, size.y });
                return 1;
            };

            static auto index_get = [](lua_State* L) {
                const auto self = lua_get_object<View>(L, "View", 1);

                if (lua_isstring(L, 2)) {
                    const std::string_view key = luaL_checkstring(L, 2);

                    if (key == "active") lua_pushcfunction(L, active);
                    else if (key == "set_port") lua_pushcfunction(L, set_port);
                    else if (key == "set_center") lua_pushcfunction(L, set_center);
                    else if (key == "set_size") lua_pushcfunction(L, set_size);
                    else if (key == "get_size") lua_pushcfunction(L, get_size);
                    else if (key == "set_zoom") lua_pushcfunction(L, set_zoom);
                    else if (key == "set_rotation") lua_pushcfunction(L, set_rotation);
                    else if (key == "get_rotation") lua_pushcfunction(L, get_rotation);
                    else if (key == "copy") lua_pushcfunction(L, copy);
                    else lua_pushnil(L);
                }
                else {
                    lua_pushnil(L);
                }

                return 1;
            };

            static auto to_string = [](lua_State* L) {
                const auto self = lua_get_object<View>(L, "View", 1);
                sf::Vector2f center_pos = self->getCenter();
                sf::Vector2f size = self->getSize();

                std::stringstream result;
                result << "{ x: " << center_pos.x - size.x / 2
                       << ", y: " << center_pos.y - size.y / 2
                       << ", w: " << size.x
                       << ", h: " << size.y
                       << " }";

                lua_pushstring(L, result.str().c_str());
                return 1;
            };

            static auto is_equal = [](lua_State* L) {
                const auto self = lua_get_object<View>(L, "View", 1);
                const auto target = lua_get_object<View>(L, "View", 2);

                lua_pushboolean(L, (
                    self->getCenter() == target->getCenter() &&
                    self->getSize() == target->getSize() &&
                    self->getRotation() == target->getRotation()
                ));
                return 1;
            };

            lua_setmethods(L, "View", {
                { "__gc", destructor },
                { "__index", index_get },
                { "__tostring", to_string },
                { "__eq", is_equal }
            });

            return 1;
        }

        static int reg(lua_State* L) {
            LuaStack tmp(L);
            lua_remove(L, -static_cast<int>(tmp.size()));

            return push_to_lua(L);
        }
    };
}