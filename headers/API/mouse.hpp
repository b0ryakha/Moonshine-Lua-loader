#pragma once

#include "lua_extensions.hpp"
#include <string>

namespace lua
{
    static int get_button_pressed(lua_State* L) {
        while (window.isOpen()) {
            if (main_event.type == sf::Event::MouseButtonPressed) {
                std::string button_name("None");
 
                switch (main_event.mouseButton.button) {
                    case sf::Mouse::Left:
                        button_name = "Left";
                        break;
                    case sf::Mouse::Right:
                        button_name = "Right";
                        break;
                    case sf::Mouse::Middle:
                        button_name = "Middle";
                        break;
                    case sf::Mouse::XButton1:
                        button_name = "XButton1";
                        break;
                    case sf::Mouse::XButton2:
                        button_name = "XButton2";
                        break;
                }

                lua_pushstring(L, button_name.c_str());
                return 1;
            }
        }
    }

    static int is_button_pressed(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 1) {
            lua_pushnil(L);
            return 1;
        }

        const int key_code = args.get<int>();

        lua_pushboolean(L, sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(key_code)));
        return 1;
    }

    static int is_scrolling_up(lua_State* L) {
        if (main_event.type == sf::Event::MouseWheelScrolled) {
            lua_pushboolean(L, main_event.mouseWheelScroll.delta > 0);
            return 1;
        }

        lua_pushboolean(L, false);
        return 1;
    }

    static int is_scrolling_down(lua_State* L) {
        if (main_event.type == sf::Event::MouseWheelScrolled) {
            lua_pushboolean(L, main_event.mouseWheelScroll.delta < 0);
            return 1;
        }

        lua_pushboolean(L, false);
        return 1;
    }
}