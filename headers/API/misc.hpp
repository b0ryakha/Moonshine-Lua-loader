#pragma once

#include "lua_extensions.hpp"
#include <SFML/Graphics.hpp>

extern sf::RenderWindow window;
extern std::string FONTS_PATH;
extern size_t print_offset;

namespace lua
{
	static int print(lua_State* L) {
        LuaStack args(L);
        std::string result;
        const size_t size = 20;

        for (int i = 0; i < args.size(); ++i) {
            std::string value;

            switch (args.get_type(i)) {
                case LuaMultiValueType::Number:
                    value = std::to_string(args.get<float>(i));
                    break;
                case LuaMultiValueType::String:
                    value = args.get<std::string>(i);
                    break;
                case LuaMultiValueType::Boolean:
                    value = args.get<bool>(i) ? "true" : "false";
                    break;
                default:
                    value = "nil";
            }

            result += value + '\t';
        }

        sf::Font font;
        if (!font.loadFromFile(FONTS_PATH + "arial.ttf"))
            throw_error("Failed to create the font face.");

        sf::Text text(sf::String::fromUtf8(result.begin(), result.end()), font, size);
        text.setPosition(sf::Vector2f(0, print_offset));
        text.setFillColor(sf::Color::White);

        window.draw(text);

        print_offset += size;

        if (print_offset >= window.getSize().y)
            print_offset = 0;

        return 0;
    }
}