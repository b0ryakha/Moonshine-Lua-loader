#pragma once

#include "lua_extensions.hpp"
#include "API/Objects/Vector2.hpp"

#include <mutex>

inline bool f_cursor_in_window = false;
inline std::mutex cursor_in_window_m;

namespace API
{
	static int cursor_get_pos(lua_State* L) {
        sf::Vector2f pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        lua_push_object<Vector2>(L, { pos.x, pos.y });
        return 1;
	}

    static int cursor_set_pos(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 2)
            throw_error("[cursor.set_pos] Incorrect number of arguments!");

        sf::Mouse::setPosition(sf::Vector2i(args.get<int>(0), args.get<int>(1)));

        return 0;
    }

    static int cursor_in_bounds(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 4)
            throw_error("[cursor.in_bounds] Incorrect number of arguments!");

        float x = args.get<float>();
        float y = args.get<float>();
        float w = args.get<float>();
        float h = args.get<float>();

        sf::Vector2f m = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        lua_pushboolean(L, (m.x >= x && m.x < x + w && m.y >= y && m.y < y + h));
        return 1;
    }

    static int cursor_in_window(lua_State* L) {
        lua_pushboolean(L, f_cursor_in_window);
        return 1;
    }
}