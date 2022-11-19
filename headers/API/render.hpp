#pragma once

#include <string>
#include <map>
#include <SFML/Graphics.hpp>

#include "lua_extensions.hpp"

extern std::map<std::string, std::pair<sf::Sprite, sf::Texture>> sprite_buffer;

namespace lua
{
    static int render_new_sprite(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 3) {
            lua_pushnil(L);
            return 1;
        }

        std::string path = args.get<std::string>(0);
        float w = args.get<float>(1);
        float h = args.get<float>(2);

        const std::string ID{ "0x" + std::to_string(sprite_buffer.size()) };
        sf::Texture texture;

        if (!texture.loadFromFile(path)) {
            lua_pushnil(L);
            return 1;
        }

        sprite_buffer[ID] = std::make_pair(sf::Sprite(texture), texture);

        lua_pushstring(L, ID.c_str());
        return 1;
    }

    static int render_text(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 6) {
            lua_pushnil(L);
            return 1;
        }

        float x = args.get<float>(0);
        float y = args.get<float>(1);
        std::string text{ args.get<std::string>(2) };
        std::string font_name{ args.get<std::string>(3) };
        size_t size = args.get<size_t>(4);
        sf::Color color = lua_get_color(args, 5);

        sf::Font font;
        if (!font.loadFromFile(FONTS_PATH + correct_font(font_name)))
            throw_error("Failed to create the font face.");

        sf::Text _text(sf::String::fromUtf8(text.begin(), text.end()), font, size);
        _text.setPosition(sf::Vector2f(x, y));
        _text.setFillColor(color);

        window.draw(_text);

        return 0;
    }
}