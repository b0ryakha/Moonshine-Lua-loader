#include "misc_functions.hpp"

void throw_error(const std::string& error) noexcept {
    sf::Font font;

    if (!font.loadFromFile(font_path + "arial.ttf")) {
        window.close();
        std::exit(0);
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

    while (window.isOpen()) {
        if (main_event.type == sf::Event::KeyPressed)
            break;
    }
    
    window.close();
    std::exit(0);
}