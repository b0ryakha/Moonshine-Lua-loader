#pragma once

#include "lua_extensions.hpp"
#include "API/Objects/Vector2.hpp"

#include <mutex>

inline bool f_cursor_in_window = false;
inline std::mutex cursor_in_window_m;

namespace API
{
	static int cursor_get_pos(lua_State* L) {
        LuaStack args(L);

        if (args.size() > 1)
            throw_error("[cursor.get_pos] Incorrect number of arguments!");

        bool is_regarding_window = (args.size() == 1 ? args.get<bool>() : true);
        int x = (is_regarding_window ? sf::Mouse::getPosition(window).x : sf::Mouse::getPosition().x);
        int y = (is_regarding_window ? sf::Mouse::getPosition(window).y : sf::Mouse::getPosition().y);

        if (is_regarding_window) {
            if (x < 0) x = 0;
            if (x > window.getSize().x) x = window.getSize().x;
            if (y < 0) y = 0;
            if (y > window.getSize().y) y = window.getSize().y;
        }

        lua_push_object<Vector2>(L, { x, y });
        return 1;
	}

    static int cursor_set_pos(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 2 && args.size() != 3)
            throw_error("Incorrect number of arguments!");

        int x = args.get<int>();
        int y = args.get<int>();
        bool is_regarding_window = (args.size() == 3 ? args.get<bool>() : true);

        if (is_regarding_window) {
            if (x < window.getPosition().x)
                x = window.getPosition().x;

            if (x > window.getPosition().x + window.getSize().x)
                x = window.getPosition().x + window.getSize().x;

            if (y < window.getPosition().y)
                y = window.getPosition().y;

            if (y > window.getPosition().y + window.getSize().y)
                y = window.getPosition().y + window.getSize().y;
        }

        sf::Mouse::setPosition(sf::Vector2i(x, y));

        return 0;
    }

    static int cursor_in_bounds(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 4 && args.size() != 5)
            throw_error("[cursor.in_bounds] Incorrect number of arguments!");

        float x = args.get<float>();
        float y = args.get<float>();
        float w = args.get<float>();
        float h = args.get<float>();
        bool is_regarding_window = (args.size() == 5 ? args.get<bool>() : true);

        if (is_regarding_window and !f_cursor_in_window) {
            lua_pushboolean(L, false);
            return 1;
        }

        int m_x = (is_regarding_window ? sf::Mouse::getPosition(window).x : sf::Mouse::getPosition().x);
        int m_y = (is_regarding_window ? sf::Mouse::getPosition(window).y : sf::Mouse::getPosition().y);

        if (is_regarding_window) {
            if (m_x < 0) m_x = 0;
            if (m_x > window.getSize().x) m_x = window.getSize().x;
            if (m_y < 0) m_y = 0;
            if (m_y > window.getSize().y) m_y = window.getSize().y;
        }

        lua_pushboolean(L, (m_x >= x && m_x < x + w && m_y >= y && m_y < y + h));
        return 1;
    }

    static int cursor_in_window(lua_State* L) {
        lua_pushboolean(L, f_cursor_in_window);
        return 1;
    }
}