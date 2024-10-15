#pragma once
#include "lua_helper.hpp"

#include "Application.hpp"
extern Application* app;

namespace API
{
    static int keyboard_get_pressed(lua_State* L) {
        LuaStack args(L, "keyboard.get_pressed");

        if (args.size() > 1)
            args.error("Incorrect number of arguments!");

        const bool is_symbol = (args.size() == 1 ? args.get<bool>() : false);

        while (app->isOpen()) {
            if (is_symbol) {
                if (app->event.type == sf::Event::TextEntered && app->event.text.unicode > 31 && app->event.text.unicode < 128) {
                    std::string tmp;
                    tmp += static_cast<char>(app->event.text.unicode);

                    lua_pushstring(L, tmp.c_str());
                    return 1;
                }
            }
            else if (app->event.type == sf::Event::KeyPressed) {
                lua_pushinteger(L, static_cast<int>(app->event.key.code));
                return 1;
            }
        }

        return 0;
    }

    static int keyboard_is_pressed(lua_State* L) {
        LuaStack args(L, "keyboard.is_pressed");

        if (args.size() != 1)
            args.error("Incorrect number of arguments!");

        lua_pushboolean(L, sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(args.get<int>())));
        return 1;
    }
}