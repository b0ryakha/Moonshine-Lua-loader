#pragma once

#include <SFML/Graphics.hpp>
#include <boost/random.hpp>
#include <chrono>
#include <thread>

extern sf::RenderWindow window;
extern std::string FONTS_PATH;

int rand_number(int min, int max);

__forceinline void throw_exception(const std::string& exception, bool close_window = true) {
    sf::Font font;
    font.loadFromFile(FONTS_PATH + "arial.ttf");

    sf::Text text(exception, font, 20);
    text.setPosition(sf::Vector2f((window.getSize().x / 2) - (exception.length() * 16) / 2, window.getSize().y / 2));
    text.setFillColor(sf::Color::Red);

    window.clear();
    window.draw(text);
    window.display();

    std::this_thread::sleep_for(std::chrono::milliseconds(4000));

    if (close_window)
        window.close();
}