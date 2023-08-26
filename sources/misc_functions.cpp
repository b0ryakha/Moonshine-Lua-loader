#include "misc_functions.hpp"

void throw_error(std::string_view error) noexcept {
    sf::Font font;

    if (!font.loadFromFile(font_path + "arial.ttf")) {
        window.close();
        std::exit(0);
    }

    sf::Text text(sf::String::fromUtf8(error.cbegin(), error.cend()), font, 20);
    sf::Text info("Press any key to continue...\n\n [CTRL + C] copy the error.", font, 20);

    text.setPosition(window.mapPixelToCoords(sf::Vector2i(
        window.getSize().x / 2 - text.getGlobalBounds().width / 2,
        window.getSize().y / 2
    )));
    
    info.setPosition(window.mapPixelToCoords(sf::Vector2i(
        window.getSize().x / 2 - info.getGlobalBounds().width / 2,
        window.getSize().y / 2 + text.getGlobalBounds().height + 10
    )));

    text.setFillColor(sf::Color::Red);
    info.setFillColor(sf::Color::Red);

    while (window.isOpen()) {
        window.clear();
        window.draw(text);
        window.draw(info);
        window.display();

        if (main_event.type == sf::Event::TextEntered && main_event.key.code == 3) { // 3 = Ctrl + C
            info.setString("Press any key to continue...");
            sf::Clipboard::setString(error.data());
        }

        if (main_event.type == sf::Event::KeyPressed) {
            if (!main_event.key.control && !main_event.key.system && !main_event.key.alt &&!main_event.key.shift)
                break;
        }
    }
    
    window.close();
    std::exit(0);
}