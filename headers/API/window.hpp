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
            //window.clear(lua_get_color(L, arg_count));
        }

        return 0;
    }

    static int refresh(lua_State* L) {
        window.display();
        return 0;
    }
}