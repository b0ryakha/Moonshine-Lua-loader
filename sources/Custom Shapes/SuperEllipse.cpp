#include "SuperEllipse.hpp"

#include <cmath>
#include <vector>

SuperEllipse::SuperEllipse(float x, float y, float w, float h, int rounding, const sf::Color& color)
    : rect({ x, y, w, h })
{
    rounding = std::min(std::max(rounding, 0), 100);
    const float max_rounding = std::min(rect.width, rect.height) / 2;

    radius = (max_rounding * rounding) / 100.f;

    std::vector<sf::Vector2f> sin_4;
    constexpr float PI_2 = 3.14159265358979323846f / 2.0f;
    constexpr float PREC = PI_2 / 15.f;

    for (float i = 0.f; i < PI_2; i += PREC)
        sin_4.emplace_back(sinf(i) * radius, cosf(i) * radius);

    const float WIDTH = rect.width - radius;
    const float HEIGHT = rect.height - radius;

    for (auto it = sin_4.crbegin(), end = sin_4.crend(); it != end; ++it)
        points.emplace_back(WIDTH + it->x, HEIGHT + it->y);

    for (const auto& point : sin_4)
        points.emplace_back(radius - point.x, HEIGHT + point.y);

    for (auto it = sin_4.crbegin(), end = sin_4.crend(); it != end; ++it)
        points.emplace_back(radius - it->x, radius - it->y);

    for (const auto& point : sin_4)
        points.emplace_back(WIDTH + point.x, radius - point.y);

    setPosition(rect.left, rect.top);
    setFillColor(color);

    sf::Shape::update();
}

size_t SuperEllipse::getPointCount() const {
    return points.size();
}

sf::Vector2f SuperEllipse::getPoint(size_t index) const {
    return points[index];
}