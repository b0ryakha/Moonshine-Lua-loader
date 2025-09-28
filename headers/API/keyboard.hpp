#pragma once
#include "Application.hpp"

namespace API
{
    static int keyboard_get_pressed(lua_State* L) {
        LuaStack args(L, "keyboard.get_pressed");

        if (args.size() > 1)
            args.error("Incorrect number of arguments!");

        const bool is_symbol = (args.size() == 1 ? args.get<bool>() : false);

        while (Application::instance()->isOpen()) {
            if (is_symbol) {
                if (Application::instance()->event.type == sf::Event::TextEntered && Application::instance()->event.text.unicode > 31 && Application::instance()->event.text.unicode < 128) {
                    std::string tmp;
                    tmp += static_cast<char>(Application::instance()->event.text.unicode);

                    lua_pushstring(L, tmp.c_str());
                    return 1;
                }
            }
            else if (Application::instance()->event.type == sf::Event::KeyPressed) {
                lua_pushinteger(L, static_cast<int>(Application::instance()->event.key.code));
                return 1;
            }
        }

        return 0;
    }

    static int keyboard_is_pressed(lua_State* L) {
        LuaStack args(L, "keyboard.is_pressed");

        if (args.size() == 0) {
            bool is_pressed_symbol = Application::instance()->event.type == sf::Event::TextEntered && Application::instance()->event.text.unicode > 31 && Application::instance()->event.text.unicode < 128;
            if (!is_pressed_symbol)
                return 0;

            std::string tmp;
            tmp += static_cast<char>(Application::instance()->event.text.unicode);
            
            lua_pushstring(L, tmp.c_str());
            return 1;
        }

        if (args.size() == 1) {
            lua_pushboolean(L, sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(args.get<int>())));
            return 1;
        }

        args.error("Incorrect number of arguments!");
        return 0;
    }
}