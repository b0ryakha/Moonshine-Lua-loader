#pragma once

#include "lua_helper.hpp"
#include "SuperEllipse.hpp"
//#include "Blur.hpp"

#include "API/Objects/Vector2.hpp"
#include "API/Objects/Color.hpp"
#include "API/Objects/Font.hpp"
#include "API/Objects/Sprite.hpp"

#include <string>

extern sf::RenderWindow* window;

namespace API
{
    static int render_sprite(lua_State* L) {
        if (lua_gettop(L) != 1)
            throw_error("[render.sprite] Incorrect number of arguments!");

        window->draw(*lhelper::get_object<Sprite>(L, "Sprite", 1));

        return 0;
    }

    static int render_measure_text(lua_State* L) {
        LuaStack args(L, "render.measure_text");

        if (args.size() != 2)
            args.error("Incorrect number of arguments!");

        Font font = args.get<LuaUserdata, Font>();
        const std::string str = args.get<std::string>();

        sf::Text text(sf::String::fromUtf8(str.cbegin(), str.cend()), font, font.get_size());
        text.setStyle(font.get_style());

        lhelper::push_object<Vector2>(L, {
            text.getGlobalBounds().width,
            text.getGlobalBounds().height
        });

        return 1;
    }

    static int render_text(lua_State* L) {
        LuaStack args(L, "render.text");

        if (args.size() != 5)
            args.error("Incorrect number of arguments!");

        int x = args.get<int>();
        int y = args.get<int>();
        Font font = args.get<LuaUserdata, Font>();
        const std::string str = args.get<std::string>();
        sf::Color color = args.get<LuaUserdata, Color>();

        sf::Text text(sf::String::fromUtf8(str.cbegin(), str.cend()), font, font.get_size());
        text.setStyle(font.get_style());
        text.setPosition(window->mapPixelToCoords(sf::Vector2i(x, y - text.getGlobalBounds().top)));
        text.setFillColor(color);
        text.setScale(
            1400.f / static_cast<float>(window->getSize().x),
            800.f / static_cast<float>(window->getSize().y)
        );

        window->draw(text);

        return 0;
    }

    static int render_rectangle(lua_State* L) {
        LuaStack args(L, "render.rectangle");

        if (args.size() != 5 && args.size() != 6)
            args.error("Incorrect number of arguments!");

        int x = args.get<int>();
        int y = args.get<int>();
        size_t w = args.get<size_t>();
        size_t h = args.get<size_t>();
        sf::Color color = args.get<LuaUserdata, Color>();
        size_t rounding = (args.size() == 6) ? args.get<size_t>() : 0;

        const auto conv_pos = window->mapPixelToCoords(sf::Vector2i(x, y));
        const auto conv_size = window->mapPixelToCoords(sf::Vector2i(w, h));

        SuperEllipse rectangle(conv_pos.x, conv_pos.y, conv_size.x, conv_size.y, rounding, color);

        window->draw(rectangle);

        return 0;
    }

    static int render_outline_rectangle(lua_State* L) {
        LuaStack args(L, "render.outline_rectangle");

        if (args.size() != 6 && args.size() != 7)
            args.error("Incorrect number of arguments!");

        int x = args.get<int>();
        int y = args.get<int>();
        size_t w = args.get<size_t>();
        size_t h = args.get<size_t>();
        float thickness = args.get<float>();
        sf::Color color = args.get<LuaUserdata, Color>();
        size_t rounding = (args.size() == 7) ? args.get<size_t>() : 0;

        const auto conv_pos = window->mapPixelToCoords(sf::Vector2i(x, y));
        const auto conv_size = window->mapPixelToCoords(sf::Vector2i(w, h));

        SuperEllipse rectangle(conv_pos.x, conv_pos.y, conv_size.x, conv_size.y, rounding, sf::Color::Transparent);
        rectangle.setOutlineColor(color);
        rectangle.setOutlineThickness(thickness);

        window->draw(rectangle);

        return 0;
    }

    static int render_circle(lua_State* L) {
        LuaStack args(L, "render.circle");

        if (args.size() != 4 && args.size() != 6)
            args.error("Incorrect number of arguments!");

        int x = args.get<int>();
        int y = args.get<int>();
        float radius = pixel_to_coord(args.get<size_t>());
        sf::Color color = args.get<LuaUserdata, Color>();
        float thickness = (args.size() == 6) ? args.get<float>() : 0.f;
        sf::Color outline_color = (args.size() == 6) ? args.get<LuaUserdata, Color>() : sf::Color();

        sf::CircleShape circle(radius);

        const auto conv_pos = window->mapPixelToCoords(sf::Vector2i(x, y));

        circle.setFillColor(color);
        circle.setPosition(sf::Vector2f(conv_pos.x - radius, conv_pos.y - radius));

        if (args.size() == 6) {
            circle.setOutlineThickness(thickness);
            circle.setOutlineColor(outline_color);
        }

        window->draw(circle);

        return 0;
    }

    static int render_line(lua_State* L) {
        LuaStack args(L, "render.line");

        if (args.size() != 6)
            args.error("Incorrect number of arguments!");

        int x1 = args.get<int>();
        int y1 = args.get<int>();
        int x2 = args.get<int>();
        int y2 = args.get<int>();
        float thickness = args.get<float>();
        sf::Color color = args.get<LuaUserdata, Color>();

        const auto conv_pos1 = window->mapPixelToCoords(sf::Vector2i(x1, y1));
        const auto conv_pos2 = window->mapPixelToCoords(sf::Vector2i(x2, y2));

        sf::Vertex line[2];

        auto draw_line = [&](const sf::Vector2f& start, const sf::Vector2f& end) {
            line[0].position = start;
            line[0].color = color;

            line[1].position = end;
            line[1].color = color;

            window->draw(line, 2, sf::Lines);
        };

        for (int i = 0; i < floor(thickness / 2); ++i)
            draw_line(sf::Vector2f(conv_pos1.x, conv_pos1.y - i), sf::Vector2f(conv_pos2.x, conv_pos2.y - i));

        for (int i = 0; i < floor(thickness / 2); ++i)
            draw_line(sf::Vector2f(conv_pos1.x, conv_pos1.y + i), sf::Vector2f(conv_pos2.x, conv_pos2.y + i));

        return 0;
    }

    static int render_polygon(lua_State* L) {
        LuaStack args(L, "render.polygon");

        if (args.size() != 2)
            args.error("Incorrect number of arguments!");

        LuaTable points = args.get<LuaTable>();
        sf::Color color = args.get<LuaUserdata, Color>();

        sf::ConvexShape polygon;

        polygon.setFillColor(color);
        polygon.setPointCount(points.size());

        for (size_t i = 0, size = points.size(); i < size; ++i) {
            LuaTable point = points.get<LuaTable>();

            if (point.size() != 2)
                args.error("Incorrect number of values!");

            polygon.setPoint(i, window->mapPixelToCoords(sf::Vector2i(point.get<int>(), point.get<int>())));
        }

        window->draw(polygon);

        return 0;
    }

    //static int render_blur(lua_State* L) {
    //    LuaStack args(L, "render.blur");
    //
    //    if (args.size() != 5 && args.size() != 6)
    //        args.error("Incorrect number of arguments!");
    //
    //    size_t x = args.get<size_t>();
    //    size_t y = args.get<size_t>();
    //    size_t w = args.get<size_t>();
    //    size_t h = args.get<size_t>();
    //    size_t strength = args.get<size_t>();
    //    size_t rounding = (args.size() == 6) ? args.get<size_t>() : 0;
    //
    //    Blur blur(x, y, w, h, strength, rounding);
    //
    //    render_buffer.display();
    //    blur.draw(render_buffer);
    //
    //    return 0;
    //}
}