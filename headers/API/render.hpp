#pragma once

#include "lua_extensions.hpp"
#include "SuperEllipse.hpp"

#include "API/Objects/Vector2.hpp"
#include "API/Objects/Color.hpp"
#include "API/Objects/Font.hpp"
#include "API/Objects/Sprite.hpp"

#include <string>

extern size_t print_offset;

namespace API
{
    static int render_measure_text(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 2)
            throw_error("[render.measure_text] Incorrect number of arguments!");

        Font font = args.get<LuaUserdata, Font>();
        std::string text = args.get<std::string>();

        sf::Text _text(sf::String::fromUtf8(text.begin(), text.end()), font, font.get_size());

        lua_push_object<Vector2>(L, {
            _text.getLocalBounds().width,
            _text.getLocalBounds().height
        });

        return 1;
    }

    static int render_sprite(lua_State* L) {
        if (lua_gettop(L) != 1)
            throw_error("Incorrect number of arguments!");

        const auto self = lua_get_object<Sprite>(L, "Sprite", 1);

        window.draw(*self);

        return 0;
    }

    static int render_text(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 5)
            throw_error("Incorrect number of arguments!");

        float x = args.get<float>();
        float y = args.get<float>();
        Font font = args.get<LuaUserdata, Font>();
        std::string text = args.get<std::string>();
        sf::Color color = args.get<LuaUserdata, Color>();

        sf::Text _text(sf::String::fromUtf8(text.begin(), text.end()), font, font.get_size());
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

    /*static int render_blur(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 6 && args.size() != 7)
            throw_error("Incorrect number of arguments!");

        float x1 = args.get<float>();
        float y1 = args.get<float>();
        float x2 = args.get<float>();
        float y2 = args.get<float>();
        float strength = args.get<float>();
        float alpha = args.get<float>();
        float rounding = args.size() == 7 ? args.get<float>() : 0;

        

        return 0;
    }*/

    static int render_polygon(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 2)
            throw_error("Incorrect number of arguments!");

        LuaTable points = args.get<LuaTable>();
        sf::Color color = args.get<LuaUserdata, Color>();

        sf::ConvexShape polygon;

        polygon.setFillColor(color);
        polygon.setPointCount(points.size());

        for (size_t i = 0, size = points.size(); i < size; ++i) {
            LuaTable point = points.get<LuaTable>();

            if (point.size() != 2)
                throw_error("[point] Incorrect number of values!");

            polygon.setPoint(i, sf::Vector2f(point.get<float>(), point.get<float>()));
        }

        window.draw(polygon);

        return 0;
    }
}