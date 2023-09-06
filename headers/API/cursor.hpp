#pragma once

#include "lua_helper.hpp"
#include "API/Objects/Vector2.hpp"

#include <mutex>

inline bool is_cursor_in_window = false;
inline std::mutex cursor_in_window_m;

namespace API
{
	static int cursor_get_pos(lua_State* L) {
        sf::Vector2i pos = sf::Mouse::getPosition(window);
        const sf::Vector2u window_size = window.getSize();

        pos.x = std::min(static_cast<size_t>(std::max(pos.x, 0)), window_size.x);
        pos.y = std::min(static_cast<size_t>(std::max(pos.y, 0)), window_size.y);

        lhelper::push_object<Vector2>(L, { pos.x, pos.y });
        return 1;
	}

    static int cursor_is_bound(lua_State* L) {
        LuaStack args(L, "cursor.is_bound");

        if (args.size() != 4)
            args.error("Incorrect number of arguments!");

        const size_t x = args.get<size_t>();
        const size_t y = args.get<size_t>();
        const size_t w = args.get<size_t>();
        const size_t h = args.get<size_t>();

        const sf::Vector2i m = sf::Mouse::getPosition(window);

        lua_pushboolean(L, (m.x >= x && m.x < x + w && m.y >= y && m.y < y + h));
        return 1;
    }

    static int cursor_in_window(lua_State* L) {
        lua_pushboolean(L, is_cursor_in_window);
        return 1;
    }
}