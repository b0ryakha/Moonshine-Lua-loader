#pragma once
#include "lua_helper.hpp"

#include "Application.hpp"
extern Application* app;

namespace API
{
    static int mouse_get_pressed(lua_State* L) {
        while (app->isOpen()) {
            if (app->event.type == sf::Event::MouseButtonPressed) {
                lua_pushinteger(L, static_cast<int>(app->event.mouseButton.button));
                return 1;
            }
        }

        return 0;
    }

    static int mouse_is_pressed(lua_State* L) {
        LuaStack args(L, "mouse.is_pressed");

        if (args.size() != 1)
            args.error("Incorrect number of arguments!");

        const int key_code = args.get<int>();

        lua_pushboolean(L, sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(key_code)));
        return 1;
    }

    static int mouse_is_scrolling_up(lua_State* L) {
        if (app->event.type == sf::Event::MouseWheelScrolled && app->event.mouseWheelScroll.delta > 0.f) {
            app->event.mouseWheelScroll.delta = 0.f;

            lua_pushboolean(L, true);
            return 1;
        }

        lua_pushboolean(L, false);
        return 1;
    }

    static int mouse_is_scrolling_down(lua_State* L) {
        if (app->event.type == sf::Event::MouseWheelScrolled && app->event.mouseWheelScroll.delta < 0.f) {
            app->event.mouseWheelScroll.delta = 0.f;

            lua_pushboolean(L, true);
            return 1;
        }

        lua_pushboolean(L, false);
        return 1;
    }
}