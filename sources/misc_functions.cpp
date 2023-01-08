#include "misc_functions.hpp"

void throw_error(const std::string& error) noexcept {
    sf::Font font;

    auto close_window = [&] {
        std::lock_guard<std::mutex> lock(closing_window_m);
        window.close();
    };

    if (!font.loadFromFile(FONTS_PATH + "arial.ttf"))
        close_window();

    sf::Text text(error, font, 20);
    text.setPosition(sf::Vector2f(window.getSize().x / 2 - text.getGlobalBounds().width / 2, window.getSize().y / 2));
    text.setFillColor(sf::Color::Red);

    sf::Text info("Press any key to continue...", font, 20);
    info.setPosition(sf::Vector2f(window.getSize().x / 2 - info.getGlobalBounds().width / 2, window.getSize().y / 2 + text.getGlobalBounds().height + 10));
    info.setFillColor(sf::Color::Red);

    window.clear();
    window.draw(text);
    window.draw(info);
    window.display();

    while (window.isOpen() && main_event.type != sf::Event::KeyPressed) {}

    close_window();
}

std::string number_to_str(double n) {
    std::string tmp = std::to_string(n);

    for (auto it = tmp.end() - 1; it >= tmp.begin(); --it) {
        if (*it == '0') it = tmp.erase(it);
        else break;
    }

    return (tmp + '0');
}