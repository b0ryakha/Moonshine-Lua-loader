#pragma once
#include "lua_helper.hpp"
#include "API/Objects/Vector2.hpp"
#include "API/Objects/Color.hpp"
#include "API/Objects/Font.hpp"
#include "API/Objects/Sprite.hpp"

#include "SuperEllipse.hpp"
//#include "Blur.hpp"

#include "Application.hpp"

namespace API
{
    static int render_sprite(lua_State* L) {
        if (lua_gettop(L) != 1)
            throw_error("[render.sprite] Incorrect number of arguments!");

        Application::instance()->draw(*lhelper::get_object<Sprite>(L, "Sprite", 1));
        return 0;
    }

    static int render_measure_text(lua_State* L) {
        LuaStack args(L, "render.measure_text");

        if (args.size() != 2)
            args.error("Incorrect number of arguments!");

        Font font = args.get<LuaUserdata, Font>();
        const std::string str = args.get<std::string>();

        float total_width = 0.0f;
        float total_height = 0.0f;
        bool is_bold = (font.get_style() & sf::Text::Style::Bold) == sf::Text::Style::Bold;

        for (char c : str) {
            auto glyph = font.getGlyph(c, font.get_size(), false);
            total_width += glyph.advance;
            total_height = std::max(total_height, glyph.bounds.height);
        }

        lhelper::push_object<Vector2>(L, {
            total_width,
            total_height
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
        text.setPosition(Application::instance()->mapPixelToCoords(sf::Vector2i(x, y - text.getGlobalBounds().top)));
        text.setFillColor(color);
        text.setScale(
            static_cast<float>(Application::instance()->getInitSize().x) / static_cast<float>(Application::instance()->getSize().x),
            static_cast<float>(Application::instance()->getInitSize().y) / static_cast<float>(Application::instance()->getSize().y)
        );

        auto width = font.getGlyph('A', font.get_size(), false).bounds.width;

        Application::instance()->draw(text);
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

        const auto conv_pos = Application::instance()->mapPixelToCoords(sf::Vector2i(x, y));
        const auto conv_size = Application::instance()->mapPixelToCoords(sf::Vector2i(w, h));

        SuperEllipse rectangle(conv_pos.x, conv_pos.y, conv_size.x, conv_size.y, rounding, color);

        Application::instance()->draw(rectangle);
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

        const auto conv_pos = Application::instance()->mapPixelToCoords(sf::Vector2i(x, y));
        const auto conv_size = Application::instance()->mapPixelToCoords(sf::Vector2i(w, h));

        SuperEllipse rectangle(conv_pos.x, conv_pos.y, conv_size.x, conv_size.y, rounding, sf::Color::Transparent);
        rectangle.setOutlineColor(color);
        rectangle.setOutlineThickness(thickness);

        Application::instance()->draw(rectangle);
        return 0;
    }

    static int render_gradient(lua_State* L) {
        LuaStack args(L, "render.gradient");

        if (args.size() != 8 && args.size() != 9)
            args.error("Incorrect number of arguments!");

        int x = args.get<int>();
        int y = args.get<int>();
        size_t w = args.get<size_t>();
        size_t h = args.get<size_t>();
        sf::Color top_left = args.get<LuaUserdata, Color>();
        sf::Color top_right = args.get<LuaUserdata, Color>();
        sf::Color bottom_left = args.get<LuaUserdata, Color>();
        sf::Color bottom_right = args.get<LuaUserdata, Color>();

        const auto conv_pos = Application::instance()->mapPixelToCoords(sf::Vector2i(x, y));
        const auto conv_size = Application::instance()->mapPixelToCoords(sf::Vector2i(w, h));

        sf::VertexArray gradient(sf::Quads, 4);

        gradient[0].position = conv_pos;
        gradient[0].color = top_left;

        gradient[1].position = sf::Vector2f(conv_pos.x + conv_size.x, conv_pos.y);
        gradient[1].color = top_right;

        gradient[2].position = sf::Vector2f(conv_pos.x + conv_size.x, conv_pos.y + conv_size.y);
        gradient[2].color = bottom_right;

        gradient[3].position = sf::Vector2f(conv_pos.x, conv_pos.y + conv_size.y);
        gradient[3].color = bottom_left;

        Application::instance()->draw(gradient);
        return 0;
    }

    static int render_circle(lua_State* L) {
        LuaStack args(L, "render.circle");

        if (args.size() != 4 && args.size() != 6)
            args.error("Incorrect number of arguments!");

        int x = args.get<int>();
        int y = args.get<int>();
        float radius = args.get<size_t>();
        sf::Color color = args.get<LuaUserdata, Color>();
        float thickness = (args.size() == 6) ? args.get<float>() : 0.f;
        sf::Color outline_color = (args.size() == 6) ? args.get<LuaUserdata, Color>() : sf::Color();

        sf::CircleShape circle(radius);
        circle.setPointCount(100);
        circle.setFillColor(color);

        const auto conv_pos = Application::instance()->mapPixelToCoords(sf::Vector2i(x, y));
        circle.setPosition(conv_pos.x - radius, conv_pos.y - radius);

        if (args.size() == 6) {
            circle.setOutlineThickness(thickness);
            circle.setOutlineColor(outline_color);
        }

        Application::instance()->draw(circle);
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

        const auto conv_pos1 = Application::instance()->mapPixelToCoords(sf::Vector2i(x1, y1));
        const auto conv_pos2 = Application::instance()->mapPixelToCoords(sf::Vector2i(x2, y2));

        float angle = atan2(conv_pos2.y - conv_pos1.y, conv_pos2.x - conv_pos1.x);
        float offsetX = thickness * 0.5f * sin(angle);
        float offsetY = thickness * 0.5f * cos(angle);

        sf::VertexArray line(sf::TrianglesStrip, 4);

        line[0].position = sf::Vector2f(conv_pos1.x - offsetX, conv_pos1.y + offsetY);
        line[0].color = color;

        line[1].position = sf::Vector2f(conv_pos1.x + offsetX, conv_pos1.y - offsetY);
        line[1].color = color;

        line[2].position = sf::Vector2f(conv_pos2.x - offsetX, conv_pos2.y + offsetY);
        line[2].color = color;

        line[3].position = sf::Vector2f(conv_pos2.x + offsetX, conv_pos2.y - offsetY);
        line[3].color = color;

        Application::instance()->draw(line);
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

            polygon.setPoint(i, Application::instance()->mapPixelToCoords(sf::Vector2i(point.get<int>(), point.get<int>())));
        }

        Application::instance()->draw(polygon);
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