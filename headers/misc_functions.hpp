#pragma once

#include <SFML/Graphics.hpp>
#include <boost/random.hpp>
#include <chrono>
#include <thread>
#include <string>

extern sf::RenderWindow window;
extern sf::Event main_event;
extern std::string FONTS_PATH;

int rand_number(int min, int max);

__forceinline void throw_error(const std::string& error, bool close_window = true) noexcept {
    sf::Font font;
    font.loadFromFile(FONTS_PATH + "arial.ttf");

    sf::Text text(error, font, 20);
    text.setPosition(sf::Vector2f(window.getSize().x / 2 - text.getGlobalBounds().width / 2, window.getSize().y / 2));
    text.setFillColor(sf::Color::Red);

    window.clear();
    window.draw(text);
    window.display();

    while (window.isOpen()) {
        switch (main_event.type) {
            case sf::Event::MouseButtonPressed:
            case sf::Event::KeyPressed:
                goto loop_break;

            case sf::Event::Closed:
                window.close();
        }
    }
    loop_break:

    if (close_window)
        window.close();
}