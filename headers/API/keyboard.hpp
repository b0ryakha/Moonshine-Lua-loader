#pragma once

#include <string>

#include "lua_extensions.hpp"

extern sf::RenderWindow window;
extern sf::Event main_event;

namespace lua
{
    static int get_key_pressed(lua_State* L) {
        LuaStack args(L);

        if (args.size() > 1) {
            lua_pushnil(L);
            return 1;
        }

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
                lua_pushnumber(L, static_cast<int>(main_event.key.code));
                return 1;
            }
        }
    }

    static int is_key_pressed(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 1) {
            lua_pushnil(L);
            return 1;
        }

        lua_pushboolean(L, sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(args.get<int>())));
        return 1;
    }
}