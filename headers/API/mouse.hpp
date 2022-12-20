#pragma once

#include "lua_extensions.hpp"

#include <string>

namespace API
{
    static int mouse_get_pressed(lua_State* L) {
        while (window.isOpen()) {
            if (main_event.type == sf::Event::MouseButtonPressed) {
                lua_pushnumber(L, static_cast<int>(main_event.mouseButton.button));
                return 1;
            }
        }
    }

    static int mouse_is_pressed(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 1)
            throw_error("[mouse.is_pressed] Incorrect number of arguments!");

        const int key_code = args.get<int>();

        lua_pushboolean(L, sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(key_code)));
        return 1;
    }

    static int mouse_is_scrolling_up(lua_State* L) {
        if (main_event.type == sf::Event::MouseWheelScrolled && main_event.mouseWheelScroll.delta > 0.f) {
            main_event.mouseWheelScroll.delta = 0.f;

            lua_pushboolean(L, true);
            return 1;
        }

        lua_pushboolean(L, false);
        return 1;
    }

    static int mouse_is_scrolling_down(lua_State* L) {
        if (main_event.type == sf::Event::MouseWheelScrolled && main_event.mouseWheelScroll.delta < 0.f) {
            main_event.mouseWheelScroll.delta = 0.f;

            lua_pushboolean(L, true);
            return 1;
        }

        lua_pushboolean(L, false);
        return 1;
    }
}