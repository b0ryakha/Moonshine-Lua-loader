#include "SuperEllipse.hpp"

void SuperEllipse::init() {
    std::vector<sf::Vector2f> sin_4;
    constexpr double PREC = M_PI_2 / 15;

    for (float i = 0; i < M_PI_2; i += PREC)
        sin_4.push_back(std::move(sf::Vector2f(sinf(i) * m_radius, cosf(i) * m_radius)));

    std::vector<sf::Vector2f> sin_4_reverse(sin_4.rbegin(), sin_4.rend());

    const float WIDTH2 = m_rect.width - m_radius;
    const float HEIGHT2 = m_rect.height - m_radius;

    for (const auto& point : sin_4_reverse)
        m_points.push_back(std::move(sf::Vector2f(WIDTH2 + point.x, HEIGHT2 + point.y)));

    for (const auto& point : sin_4)
        m_points.push_back(std::move(sf::Vector2f(m_radius - point.x, HEIGHT2 + point.y)));

    for (const auto& point : sin_4_reverse)
        m_points.push_back(std::move(sf::Vector2f(m_radius - point.x, m_radius - point.y)));

    for (const auto& point : sin_4)
        m_points.push_back(std::move(sf::Vector2f(WIDTH2 + point.x, m_radius - point.y)));
}

SuperEllipse::SuperEllipse() {};

SuperEllipse::SuperEllipse(const sf::Rect<float>& rect, size_t rounding, const sf::Color& color) : m_rect(rect) {
    rounding = std::min(std::max(rounding, 0u), 100u);
    const float max_rounding = std::min(rect.width, rect.height) / 2;

    m_radius = (max_rounding * rounding) / 100;

    init();
    setPosition(rect.left, rect.top);
    setFillColor(color);
    sf::Shape::update();
}

size_t SuperEllipse::getPointCount() const {
    return m_points.size();
}

sf::Vector2f SuperEllipse::getPoint(size_t index) const {
    return m_points[index];
}