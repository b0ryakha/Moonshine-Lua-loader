#pragma once

#include <string>
#include <map>

#include "lua_extensions.hpp"

extern size_t print_offset;

namespace lua
{
    static std::map<std::string, std::pair<sf::Sprite, sf::Texture>> sprite_buffer;
    static std::map<std::string, std::pair<sf::Font, size_t>> font_buffer;

    static int render_create_sprite(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 3 && args.size() != 7) {
            lua_pushnil(L);
            return 1;
        }

        std::string path = args.get<std::string>();
        float w = args.get<float>();
        float h = args.get<float>();
        float t_x = (args.size() == 7 ? args.get<float>() : 0);
        float t_y = (args.size() == 7 ? args.get<float>() : 0);
        size_t t_w = (args.size() == 7 ? args.get<size_t>() : 0);
        size_t t_h = (args.size() == 7 ? args.get<size_t>() : 0);

        const std::string ID = "0x115112114105116101" + std::to_string(sprite_buffer.size());

        sf::Texture texture;
        if (!texture.loadFromFile(path)) {
            lua_pushnil(L);
            return 1;
        }

        if (args.size() == 3) {
            t_w = texture.getSize().x;
            t_h = texture.getSize().y;
        }

        sf::Sprite sprite(texture);

        sprite.setScale(sf::Vector2(w / t_w, h / t_h));

        if (args.size() == 7)
            sprite.setTextureRect(sf::IntRect(t_x, t_y, t_w, t_h));

        sprite_buffer[ID] = std::make_pair(sprite, texture);

        lua_pushstring(L, ID.c_str());
        return 1;
    }

    static int render_create_font(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 2) {
            lua_pushnil(L);
            return 1;
        }

        std::string font_name = args.get<std::string>();
        size_t size = args.get<size_t>();

        if (font_name.length() > 4) {
            if (std::string(font_name.end() - 4, font_name.end()) != ".ttf") {
                font_name += ".ttf";
            }
        }
        else {
            font_name += ".ttf";
        }

        sf::Font font;
        if (!font.loadFromFile(FONTS_PATH + font_name)) {
            lua_pushnil(L);
            return 1;
        }

        const std::string ID = "0x102111110116" + std::to_string(font_buffer.size());

        font_buffer[ID] = std::make_pair(font, size);

        lua_pushstring(L, ID.c_str());
        return 1;
    }

    static int render_measure_text(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 2) {
            lua_pushnil(L);
            return 1;
        }

        std::string font_id = args.get<std::string>();
        std::string text = args.get<std::string>();

        sf::Font* font = nullptr;
        size_t* size = nullptr;

        try {
            font = &font_buffer[font_id].first;
            size = &font_buffer[font_id].second;
        }
        catch (...) {
            lua_pushnil(L);
            return 1;
        }

        sf::Text _text(sf::String::fromUtf8(text.begin(), text.end()), *font, *size);

        lua_pushtable(L, {
            std::make_pair("w", _text.getLocalBounds().width),
            std::make_pair("h", _text.getLocalBounds().height)
        });

        return 1;
    }

    static int render_text(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 5)
            throw_error("Incorrect number of arguments!");

        float x = args.get<float>();
        float y = args.get<float>();
        std::string font_id = args.get<std::string>();
        std::string text = args.get<std::string>();
        sf::Color color = lua_getcolor(args);

        sf::Font* font = nullptr;
        size_t* size = nullptr;

        try {
            font = &font_buffer[font_id].first;
            size = &font_buffer[font_id].second;
        }
        catch (const std::out_of_range& exception) {
            throw_error(exception.what());
        }

        sf::Text _text(sf::String::fromUtf8(text.begin(), text.end()), *font, *size);
        _text.setPosition(sf::Vector2f(x, y));
        _text.setFillColor(color);

        window.draw(_text);

        return 0;
    }

    static int render_sprite(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 3 && args.size() != 4)
            throw_error("Incorrect number of arguments!");

        std::string sprite_id = args.get<std::string>();
        float x = args.get<float>();
        float y = args.get<float>();
        sf::Color color = (args.size() == 4 ? lua_getcolor(args) : sf::Color());

        sf::Sprite* sprite = nullptr;
        sf::Texture* texture = nullptr;

        try {
            sprite = &sprite_buffer[sprite_id].first;
            texture = &sprite_buffer[sprite_id].second;
        }
        catch (const std::out_of_range& exception) {
            throw_error(exception.what());
        }

        sprite->setPosition(sf::Vector2f(x, y));
        sprite->setTexture(*texture);

        if (args.size() == 4)
            sprite->setColor(color);

        window.draw(*sprite);

        return 0;
    }
}