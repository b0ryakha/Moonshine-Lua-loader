#pragma once
#include "lua_helper.hpp"
#include "API/Objects/Vector2.hpp"

#include "Application.hpp"

#include <mutex>

inline bool is_cursor_in_window = false;
inline std::mutex cursor_in_window_m;

namespace API
{
	static int cursor_get_pos(lua_State* L) {
        sf::Vector2i pos = sf::Mouse::getPosition(*Application::instance());
        const sf::Vector2u window_size = Application::instance()->getSize();

        pos.x = std::min(static_cast<unsigned>(std::max(pos.x, 0)), window_size.x);
        pos.y = std::min(static_cast<unsigned>(std::max(pos.y, 0)), window_size.y);

        lhelper::push_object<Vector2>(L, {
            lua_Number(pos.x),
            lua_Number(pos.y)
        });

        return 1;
	}

    static int cursor_is_bound(lua_State* L) {
        LuaStack args(L, "cursor.is_bound");

        if (args.size() != 4)
            args.error("Incorrect number of arguments!");

        const int x = args.get<int>();
        const int y = args.get<int>();
        const int w = args.get<int>();
        const int h = args.get<int>();

        const sf::Vector2i m = sf::Mouse::getPosition(*Application::instance());

        lua_pushboolean(L, (m.x >= x && m.x < x + w && m.y >= y && m.y < y + h));
        return 1;
    }

    static int cursor_in_window(lua_State* L) {
        lua_pushboolean(L, is_cursor_in_window);
        return 1;
    }

    static int cursor_change_type(lua_State* L) {
        LuaStack args(L, "cursor.change_type");

        if (args.size() != 1)
            args.error("Incorrect number of arguments!");

        sf::Cursor c;
        if (!c.loadFromSystem(static_cast<sf::Cursor::Type>(args.get<int>())))
            args.error("Incorrect cursor type!");

        Application::instance()->setMouseCursor(c);
        return 0;
    }
}