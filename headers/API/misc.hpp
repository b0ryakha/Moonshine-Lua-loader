#pragma once

#include "lua_extensions.hpp"

extern sf::RenderWindow window;
extern std::string font_path;
inline sf::Vector2f print_offset{ 0.f, 0.f };

namespace API
{
	static int print(lua_State* L) {
        std::string result;

        for (size_t i = 1, args_size = lua_gettop(L); i <= args_size; ++i) {
            switch (lua_type(L, i)) {
                case LUA_TFUNCTION:
                    result += "'function'\t";
                    break;
                case LUA_TTABLE:
                    result += "'table'\t";
                    break;
                case LUA_TUSERDATA:
                    result += "'userdata'\t";
                    break;
                case LUA_TLIGHTUSERDATA:
                    result += "'lightuserdata'\t";
                    break;
                case LUA_TTHREAD:
                    result += "'thread'\t";
                    break;
                case LUA_TNIL:
                    result += "nil\t";
                    break;
                default:
                    result += std::string(lua_tostring(L, i)) + '\t';
            }
        }

        sf::Font font;
        if (!font.loadFromFile(font_path + "arial.ttf"))
            throw_error("[print] Failed to create the font face.");

        sf::Text text(sf::String::fromUtf8(result.begin(), result.end()), font, 20);
        text.setPosition(print_offset);
        text.setFillColor(sf::Color::White);

        window.draw(text);

        print_offset.y += text.getLocalBounds().height;

        if (print_offset.y >= window.getSize().y) {
            print_offset.x += text.getLocalBounds().width;
            print_offset.y = 0.f;
        }

        if (print_offset.x >= window.getSize().x)
            print_offset = { 0.f, 0.f };

        return 0;
    }
}