#pragma once

#include <SFML/Graphics.hpp>

#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>

class SuperEllipse : public sf::ConvexShape {
private:
    sf::FloatRect m_rect = { 0, 0, 0, 0 };
    sf::Vector2f m_position = { 0, 0 };
    std::vector<sf::Vector2f> m_points;

    float m_radius = 0;

    void init();

public:
    SuperEllipse(const sf::Rect<float>& rect, float radius, const sf::Color& color = sf::Color::White);

    virtual size_t getPointCount() const;
    virtual sf::Vector2f getPoint(size_t index) const;
};