#pragma once

#include "lua_extensions.hpp"
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

        lua_push_object<Vector2>(L, { pos.x, pos.y });
        return 1;
	}

    static int cursor_is_bound(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 4)
            throw_error("[cursor.is_bound] Incorrect number of arguments!");

        const float x = args.get<float>();
        const float y = args.get<float>();
        const float w = args.get<float>();
        const float h = args.get<float>();

        const sf::Vector2i m = sf::Mouse::getPosition(window);

        lua_pushboolean(L, (m.x >= x && m.x < x + w && m.y >= y && m.y < y + h));
        return 1;
    }

    static int cursor_in_window(lua_State* L) {
        lua_pushboolean(L, is_cursor_in_window);
        return 1;
    }
}