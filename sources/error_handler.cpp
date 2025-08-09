#include "error_handler.hpp"

#include "Application.hpp"

void throw_error(std::string error) {
    sf::Font font;
    if (!font.loadFromFile(Application::instance()->font_path + "Arial.TTF"))
        Application::instance()->close();

    constexpr size_t max_len = 700;
    if (error.length() > max_len) {
        auto index = error.rfind('\n', max_len);
        auto new_error = error.substr(0, index == std::string::npos ? max_len : index) + "\n\t...";
        error = std::move(new_error);
    }

    sf::Text text(sf::String::fromUtf8(error.cbegin(), error.cend()), font, 20);
    sf::Text info("Press any key to continue...\n\n [CTRL + C] copy the full error.", font, 20);

    text.setPosition(Application::instance()->mapPixelToCoords(sf::Vector2i(
        std::round(Application::instance()->getSize().x / 2.f - text.getGlobalBounds().width / 2.f),
        std::round(Application::instance()->getSize().y / 2.f - text.getGlobalBounds().height / 2.f)
    )));
    
    info.setPosition(Application::instance()->mapPixelToCoords(sf::Vector2i(
        std::round(Application::instance()->getSize().x / 2.f - info.getGlobalBounds().width / 2.f),
        std::round(Application::instance()->getSize().y / 2.f + text.getGlobalBounds().height / 2.f + 10.f)
    )));

    text.setFillColor(sf::Color::Red);
    info.setFillColor(sf::Color::Red);

    Application::instance()->event.type = sf::Event::GainedFocus;

    while (Application::instance()->isOpen()) {
        Application::instance()->clear();
        Application::instance()->draw(text);
        Application::instance()->draw(info);
        Application::instance()->display();

        if (Application::instance()->event.type == sf::Event::TextEntered) {
            if (Application::instance()->event.key.code != 3) // 3 = Ctrl + C
                break;
                
            info.setString("Press any key to continue...");
            sf::Clipboard::setString(error.data());
        }
    }
    
    Application::instance()->close();
}