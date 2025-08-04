#include "misc_functions.hpp"

#include "Application.hpp"

void throw_error(std::string_view error) {
    sf::Font font;
    if (!font.openFromFile(Application::instance()->font_path + "Arial.TTF"))
        Application::instance()->close();

    sf::Text text(font, sf::String::fromUtf8(error.cbegin(), error.cend()), 20);
    sf::Text info(font, "Press any key to continue...\n\n [CTRL + C] copy the error.", 20);

    text.setPosition(Application::instance()->mapPixelToCoords(sf::Vector2i(
        std::round(Application::instance()->getSize().x / 2.f - text.getGlobalBounds().size.x / 2.f),
        std::round(Application::instance()->getSize().y / 2.f)
    )));
    
    info.setPosition(Application::instance()->mapPixelToCoords(sf::Vector2i(
        std::round(Application::instance()->getSize().x / 2.f - info.getGlobalBounds().size.x / 2.f),
        std::round(Application::instance()->getSize().y / 2.f + text.getGlobalBounds().size.y + 10.f)
    )));

    text.setFillColor(sf::Color::Red);
    info.setFillColor(sf::Color::Red);

    Application::instance()->requestFocus();

    while (Application::instance()->isOpen()) {
        auto event = Application::instance()->pollEvent();
        if (!event.has_value()) continue;
        
        Application::instance()->clear();
        Application::instance()->draw(text);
        Application::instance()->draw(info);
        Application::instance()->display();

        if (event->is<sf::Event::TextEntered>()) {
            //TODO: impl for 3.0.0
            //if (Application::instance()->event.key.code != 3) // 3 = Ctrl + C
            //    break;
                
            info.setString("Press any key to continue...");
            sf::Clipboard::setString(error.data());
        }
    }
    
    Application::instance()->close();
}