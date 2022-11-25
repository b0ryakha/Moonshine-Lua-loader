#pragma once

#include <string>

#include "lua_extensions.hpp"

extern sf::RenderWindow window;
extern sf::Event main_event;

namespace lua
{
    static int get_pressed(lua_State* L) {
        LuaStack args(L);

        if (args.size() > 1) {
            lua_pushnil(L);
            return 1;
        }

        const bool key_code = (args.size() == 1 ? args.get<bool>() : false);

        while (window.isOpen()) {
            switch (main_event.type) {
                case sf::Event::TextEntered:
                    if (main_event.text.unicode < 128) {
                        if (key_code) {
                            lua_pushnumber(L, main_event.text.unicode);
                            return 1;
                        }
                        else {
                            std::string result;
                            result = static_cast<char>(main_event.text.unicode);

                            lua_pushstring(L, result.c_str());
                            return 1;
                        }
                    }

                    lua_pushnil(L);
                    return 1;
            }
        }
    }
}