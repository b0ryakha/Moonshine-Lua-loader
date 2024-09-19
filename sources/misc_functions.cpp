#include "misc_functions.hpp"

void throw_error(std::string_view error) {
    sf::Font font;

    if (!font.loadFromFile(font_path + "Arial.TTF")) {
        window->close();
        std::exit(0);
    }

    sf::Text text(sf::String::fromUtf8(error.cbegin(), error.cend()), font, 20);
    sf::Text info("Press any key to continue...\n\n [CTRL + C] copy the error.", font, 20);

    text.setPosition(window->mapPixelToCoords(sf::Vector2i(
        std::round(window->getSize().x / 2.f - text.getGlobalBounds().width / 2.f),
        std::round(window->getSize().y / 2.f)
    )));
    
    info.setPosition(window->mapPixelToCoords(sf::Vector2i(
        std::round(window->getSize().x / 2.f - info.getGlobalBounds().width / 2.f),
        std::round(window->getSize().y / 2.f + text.getGlobalBounds().height + 10.f)
    )));

    text.setFillColor(sf::Color::Red);
    info.setFillColor(sf::Color::Red);

    while (window->isOpen()) {
        window->clear();
        window->draw(text);
        window->draw(info);
        window->display();

        if (main_event->type == sf::Event::TextEntered) {
            if (main_event->key.code != 3) // 3 = Ctrl + C
                break;
                
            info.setString("Press any key to continue...");
            sf::Clipboard::setString(error.data());
        }
    }
    
    window->close();
    std::exit(0);
}