#pragma once

#include "lua_extensions.hpp"

#include <string>

extern sf::RenderWindow window;
extern sf::Event main_event;

namespace API
{
    static int keyboard_get_pressed(lua_State* L) {
        LuaStack args(L, "keyboard.get_pressed");

        if (args.size() > 1)
            args.error("Incorrect number of arguments!");

        const bool is_symbol = (args.size() == 1 ? args.get<bool>() : false);

        while (window.isOpen()) {
            if (is_symbol) {
                if (main_event.type == sf::Event::TextEntered && main_event.text.unicode > 31 && main_event.text.unicode < 128) {
                    std::string tmp;
                    tmp += static_cast<char>(main_event.text.unicode);

                    lua_pushstring(L, tmp.c_str());
                    return 1;
                }
            }
            else if (main_event.type == sf::Event::KeyPressed) {
                lua_pushinteger(L, static_cast<int>(main_event.key.code));
                return 1;
            }
        }
    }

    static int keyboard_is_pressed(lua_State* L) {
        LuaStack args(L, "keyboard.is_pressed");

        if (args.size() != 1)
            args.error("Incorrect number of arguments!");

        lua_pushboolean(L, sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(args.get<int>())));
        return 1;
    }
}