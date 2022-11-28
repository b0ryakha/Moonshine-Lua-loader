#pragma once

#include "lua_extensions.hpp"

namespace lua
{
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
}