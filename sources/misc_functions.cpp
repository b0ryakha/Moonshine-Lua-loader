#include "misc_functions.hpp"

int rand_number(int min, int max) {
    boost::random::mt19937 gen{ static_cast<uint32_t>(time(0) + rand()) };
    boost::random::uniform_int_distribution<> dist{ min, max };

    return dist(gen);
}

void throw_error(const std::string& error, bool is_close_window) noexcept {
    sf::Font font;

    auto close_window = [&] {
        std::lock_guard<std::mutex> lock(closing_window_m);
        window.close();
    };

    if (!font.loadFromFile(FONTS_PATH + "arial.ttf"))
        close_window();

    sf::Color color = is_close_window ? sf::Color::Red : sf::Color(255, 205, 0);

    sf::Text text(error, font, 20);
    text.setPosition(sf::Vector2f(window.getSize().x / 2 - text.getGlobalBounds().width / 2, window.getSize().y / 2));
    text.setFillColor(color);

    sf::Text info("Press any key to continue...", font, 20);
    info.setPosition(sf::Vector2f(window.getSize().x / 2 - info.getGlobalBounds().width / 2, window.getSize().y / 2 + text.getGlobalBounds().height + 10));
    info.setFillColor(color);

    window.clear();
    window.draw(text);
    window.draw(info);
    window.display();

    while (window.isOpen()) {
        if (main_event.type == sf::Event::KeyPressed)
            break;
    }

    if (is_close_window)
        close_window();
}