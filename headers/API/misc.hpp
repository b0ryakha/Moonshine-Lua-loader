#pragma once

#include "lua_extensions.hpp"
#include <SFML/Graphics.hpp>

extern sf::RenderWindow window;
extern std::string FONTS_PATH;

namespace lua
{
	static size_t offset_y = 0;

	static int print(lua_State* L) {
        int arg_count = lua_gettop(L);
        if (arg_count == 0) return 0;

        std::string result;
        const size_t size = 20;

        for (int i = 1; i <= arg_count; ++i) {
            if (lua_isnil(L, lua_gettop(L)) || lua_isnone(L, lua_gettop(L)) || lua_istable(L, lua_gettop(L)))
                continue;

            result = lua_get_value<std::string>(L) + "   " + result;

            lua_pop(L, 1);
        }

        sf::Font font;
        font.loadFromFile(FONTS_PATH + "arial.ttf");

        sf::Text text(sf::String::fromUtf8(result.begin(), result.end()), font, size);
        text.setPosition(sf::Vector2f(0, offset_y));
        text.setFillColor(sf::Color::White);

        window.draw(text);

        offset_y += size;

        if (offset_y >= window.getSize().y)
            offset_y = 0;

        return 0;
    }
}