#pragma once

#include "lua_extensions.hpp"

extern sf::RenderWindow window;

namespace lua
{
    static int close(lua_State* L) {
        window.close();
        return 0;
    }

    static int clear(lua_State* L) {
        LuaStack args(L);

        if (args.empty()) {
            window.clear();
        }
        else if (args.size() == 1) {
            window.clear(lua_getcolor(L, 0));
        }

        return 0;
    }

    static int display(lua_State* L) {
        window.display();
        return 0;
    }

    static int get_size(lua_State* L) {
        LuaStack args(L);

        lua_pushtable(L, {
            std::make_pair("w", window.getSize().x),
            std::make_pair("h", window.getSize().y)
        });

        return 1;
    }
}