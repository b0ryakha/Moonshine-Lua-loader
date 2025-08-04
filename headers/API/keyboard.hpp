#pragma once
#include "lua_helper.hpp"

#include "Application.hpp"

namespace API
{
    static int keyboard_get_pressed(lua_State* L) {
        LuaStack args(L, "keyboard.get_pressed");

        if (args.size() > 1)
            args.error("Incorrect number of arguments!");

        const bool is_symbol = (args.size() == 1 ? args.get<bool>() : false);

        while (Application::instance()->isOpen()) {
            auto event = Application::instance()->pollEvent();
            if (!event.has_value()) continue;

            if (is_symbol) {
                if (event->is<sf::Event::TextEntered>()) {
                    auto unicode = event->getIf<sf::Event::TextEntered>()->unicode;
                    if (unicode > 31 && unicode < 128) {
                        std::string tmp;
                        tmp += static_cast<char>(unicode);

                        lua_pushstring(L, tmp.c_str());
                        return 1;
                    }
                }
            }
            else if (event->is<sf::Event::KeyPressed>()) {
                auto code = event->getIf<sf::Event::KeyPressed>()->code;

                lua_pushinteger(L, static_cast<int>(code));
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