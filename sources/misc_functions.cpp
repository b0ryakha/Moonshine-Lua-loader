#include "misc_functions.hpp"

#include "Application.hpp"
extern Application* app;

void throw_error(std::string_view error) {
    sf::Font font;
    if (!font.loadFromFile(app->font_path + "Arial.TTF"))
        app->close();

    sf::Text text(sf::String::fromUtf8(error.cbegin(), error.cend()), font, 20);
    sf::Text info("Press any key to continue...\n\n [CTRL + C] copy the error.", font, 20);

    text.setPosition(app->mapPixelToCoords(sf::Vector2i(
        std::round(app->getSize().x / 2.f - text.getGlobalBounds().width / 2.f),
        std::round(app->getSize().y / 2.f)
    )));
    
    info.setPosition(app->mapPixelToCoords(sf::Vector2i(
        std::round(app->getSize().x / 2.f - info.getGlobalBounds().width / 2.f),
        std::round(app->getSize().y / 2.f + text.getGlobalBounds().height + 10.f)
    )));

    text.setFillColor(sf::Color::Red);
    info.setFillColor(sf::Color::Red);

    app->event.type = sf::Event::GainedFocus;

    while (app->isOpen()) {
        app->clear();
        app->draw(text);
        app->draw(info);
        app->display();

        if (app->event.type == sf::Event::TextEntered) {
            if (app->event.key.code != 3) // 3 = Ctrl + C
                break;
                
            info.setString("Press any key to continue...");
            sf::Clipboard::setString(error.data());
        }
    }
    
    app->close();
}