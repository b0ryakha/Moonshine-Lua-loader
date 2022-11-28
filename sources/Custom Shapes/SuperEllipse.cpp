#include "SuperEllipse.hpp"

void SuperEllipse::init() {
    std::vector<sf::Vector2f> sin_4;
    constexpr double PREC = M_PI_2 / 15;

    for (float i = 0; i < M_PI_2; i += PREC)
        sin_4.push_back({ sinf(i) * m_radius, cosf(i) * m_radius });

    std::vector<sf::Vector2f> sin_4_reverse(sin_4.rbegin(), sin_4.rend());

    const float WIDE2 = m_rect.width - m_radius;
    const float HEIGHT2 = m_rect.height - m_radius;

    for (const auto& point : sin_4_reverse)
        m_points.push_back({ WIDE2 + point.x, HEIGHT2 + point.y });

    for (const auto& point : sin_4)
        m_points.push_back({ m_radius - point.x, HEIGHT2 + point.y });

    for (const auto& point : sin_4_reverse)
        m_points.push_back({ m_radius - point.x, m_radius - point.y });

    for (const auto& point : sin_4)
        m_points.push_back({ WIDE2 + point.x, m_radius - point.y });
}

SuperEllipse::SuperEllipse(const sf::Rect<float>& rect, float radius, const sf::Color& color) : m_rect(rect), m_radius(radius) {
    init();
    setPosition(rect.left, rect.top);
    setFillColor(color);
    sf::Shape::update();
}

size_t SuperEllipse::get_point_count() const {
    return m_points.size();
}

sf::Vector2f SuperEllipse::get_point(size_t index) const {
    return m_points[index];
}