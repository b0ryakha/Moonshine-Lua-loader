#pragma once

#include "lua_extensions.h"

extern sf::RenderWindow window;

namespace lua
{
    static int close(lua_State* L) {
        window.close();
        return 0;
    }

    static int clear(lua_State* L) {
        int arg_count = lua_gettop(L);

        if (arg_count == 0) {
            window.clear();
        }
        else if (arg_count == 1) {
            window.clear(lua_get_color(L, arg_count));
        }

        return 0;
    }

    static int refresh(lua_State* L) {
        window.display();
        return 0;
    }
}