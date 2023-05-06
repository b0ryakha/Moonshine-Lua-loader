#include "misc_functions.hpp"

void throw_error(const std::string& error) noexcept {
    sf::Font font;

    if (!font.loadFromFile(FONTS_PATH + "arial.ttf")) {
        window.close();
        std::abort();
    }

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

    while (window.isOpen() && main_event.type != sf::Event::KeyPressed)
        std::this_thread::sleep_for(std::chrono::seconds(1));

    window.close();
    std::abort();
}