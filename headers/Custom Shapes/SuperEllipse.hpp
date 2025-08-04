#pragma once
#include <SFML/Graphics.hpp>

class SuperEllipse : public sf::ConvexShape {
private:
    sf::FloatRect rect;
    std::vector<sf::Vector2f> points;
    float radius = 0.f;

public:
    SuperEllipse() = default;
    explicit SuperEllipse(float x, float y, float w, float h, int rounding, const sf::Color& color = sf::Color::White);

    virtual size_t getPointCount() const;
    virtual sf::Vector2f getPoint(size_t index) const;
};