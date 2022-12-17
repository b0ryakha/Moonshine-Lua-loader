#pragma once

#include <string>
#include <unordered_map>

#include "lua_extensions.hpp"
#include "SuperEllipse.hpp"

#include "API/Objects/Vector2.hpp"
#include "API/Objects/Color.hpp"

extern size_t print_offset;

namespace API
{
    static std::unordered_map<std::string, std::pair<sf::Sprite, sf::Texture>> sprite_buffer;
    static std::unordered_map<std::string, std::pair<sf::Font, size_t>> font_buffer;

    static int render_create_sprite(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 3 && args.size() != 7)
            throw_error("[render.create_sprite] Incorrect number of arguments!");

        std::string path = args.get<std::string>();
        float w = args.get<float>();
        float h = args.get<float>();
        float t_x = (args.size() == 7 ? args.get<float>() : 0);
        float t_y = (args.size() == 7 ? args.get<float>() : 0);
        size_t t_w = (args.size() == 7 ? args.get<size_t>() : 0);
        size_t t_h = (args.size() == 7 ? args.get<size_t>() : 0);

        const std::string ID = "0x115112114105116101" + std::to_string(sprite_buffer.size());

        sf::Texture texture;
        if (!texture.loadFromFile(path))
            throw_error("[render.create_sprite] The texture cannot be found in the path '" + path + "'!");

        if (args.size() == 3) {
            t_w = texture.getSize().x;
            t_h = texture.getSize().y;
        }

        sf::Sprite sprite(texture);

        sprite.setScale(sf::Vector2(w / t_w, h / t_h));

        if (args.size() == 7)
            sprite.setTextureRect(sf::IntRect(t_x, t_y, t_w, t_h));

        sprite_buffer[ID] = std::move(std::make_pair(sprite, texture));

        lua_pushstring(L, ID.c_str());
        return 1;
    }

    static int render_create_font(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 2)
            throw_error("[render.create_font] Incorrect number of arguments!");

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
        if (!font.loadFromFile(FONTS_PATH + font_name))
            throw_error("[render.create_font] Font '" + font_name + "' not found!");

        const std::string ID = "0x102111110116" + std::to_string(font_buffer.size());

        font_buffer[ID] = std::move(std::make_pair(font, size));

        lua_pushstring(L, ID.c_str());
        return 1;
    }

    static int render_measure_text(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 2)
            throw_error("[render.measure_text] Incorrect number of arguments!");

        std::string font_id = args.get<std::string>();
        std::string text = args.get<std::string>();

        sf::Font* font = nullptr;
        size_t* size = nullptr;

        try {
            font = &font_buffer[font_id].first;
            size = &font_buffer[font_id].second;
        }
        catch (...) {
            throw_error("[render.measure_text] Font object not found!");
        }

        sf::Text _text(sf::String::fromUtf8(text.begin(), text.end()), *font, *size);

        lua_push_object<Vector2_new>(L, {
            _text.getLocalBounds().width,
            _text.getLocalBounds().height
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
        sf::Color color = args.get<LuaUserdata, Color>();

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

    static int render_rectangle(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 5 && args.size() != 6)
            throw_error("Incorrect number of arguments!");

        float x = args.get<float>();
        float y = args.get<float>();
        float w = args.get<float>();
        float h = args.get<float>();
        sf::Color color = args.get<LuaUserdata, Color>();
        float rounding = (args.size() == 6) ? args.get<float>() : 0;

        SuperEllipse rectangle(sf::Rect<float>(x, y, w, h), rounding, color);

        window.draw(rectangle);

        return 0;
    }

    static int render_circle(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 4 && args.size() != 6)
            throw_error("Incorrect number of arguments!");

        float x = args.get<float>();
        float y = args.get<float>();
        float radius = args.get<float>();
        sf::Color color = args.get<LuaUserdata, Color>();
        float thickness = (args.size() == 6) ? args.get<float>() : 0;
        sf::Color outline_color = (args.size() == 6) ? args.get<LuaUserdata, Color>() : sf::Color();

        sf::CircleShape circle(radius);

        circle.setFillColor(color);
        circle.setPosition(sf::Vector2f(x - radius, y - radius));

        if (args.size() == 6) {
            circle.setOutlineThickness(thickness);
            circle.setOutlineColor(outline_color);
        }

        window.draw(circle);

        return 0;
    }

    static int render_line(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 6)
            throw_error("Incorrect number of arguments!");

        float x1 = args.get<float>();
        float y1 = args.get<float>();
        float x2 = args.get<float>();
        float y2 = args.get<float>();
        float thickness = args.get<float>();
        sf::Color color = args.get<LuaUserdata, Color>();

        sf::Vertex line[2];

        auto draw_line = [&](const sf::Vector2f& start, const sf::Vector2f& end) {
            line[0].position = start;
            line[0].color = color;

            line[1].position = end;
            line[1].color = color;

            window.draw(line, 2, sf::Lines);
        };

        for (float i = 0; i < thickness / 2; ++i)
            draw_line(sf::Vector2f(x1, y1 - i), sf::Vector2f(x2, y2 - i));

        for (float i = 0; i < thickness / 2; ++i)
            draw_line(sf::Vector2f(x1, y1 + i), sf::Vector2f(x2, y2 + i));

        return 0;
    }

    static int render_polygon(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 2)
            throw_error("Incorrect number of arguments!");

        LuaTable points = args.get<LuaTable>();
        sf::Color color = args.get<LuaUserdata, Color>();

        sf::ConvexShape polygon;

        polygon.setFillColor(color);
        polygon.setPointCount(points.size());

        for (size_t i = 0; i < points.size(); ++i) {
            LuaTable point = points.get<LuaTable>();

            if (point.size() != 2)
                throw_error("[point] Incorrect number of values!");

            polygon.setPoint(i, sf::Vector2f(point.get<float>(), point.get<float>()));
        }

        window.draw(polygon);

        return 0;
    }

    static int render_sprite(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 3 && args.size() != 4)
            throw_error("Incorrect number of arguments!");

        std::string sprite_id = args.get<std::string>();
        float x = args.get<float>();
        float y = args.get<float>();
        sf::Color color = (args.size() == 4 ? args.get<LuaUserdata, Color>() : sf::Color());

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