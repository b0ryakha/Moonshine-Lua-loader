#pragma once

#include <SFML/Graphics.hpp>
#include <stack>

#include "Label.hpp"

class TextBox final {
private:
    sf::RectangleShape outer_rect;
    sf::RectangleShape inner_rect;
    sf::RectangleShape blinker;

    std::string text;
    std::string text_input;

    sf::Clock clock;
    sf::Time time = sf::Time::Zero;
    Label label;

    std::stack<std::string> cache;

    size_t text_size = 0;
    size_t focus_char = 0;
    float char_width = 0;
    float thickness = 0;
    float pos_x = 0;
    float pos_y = 0;
    float height = 0;
    float width = 0;
    bool is_focus = false;
    bool show_bg = false;

public:
    TextBox(const std::string& font_path, float x, float y, float w, float h, bool background = true);

    void draw(sf::RenderWindow& window);
    void handleEvent(sf::Event& event);
    std::string getText() const;

    void setSize(float w, float h);
    void setPosition(float x, float y);
    void setBorder(float t);
    bool isEntered() const;

    void setTextColor(const sf::Color& color);
    void setBackgroundColor(const sf::Color& color);
    void setBlinkerColor(const sf::Color& color);
    void setBorderColor(const sf::Color& color);
    void focus();
};