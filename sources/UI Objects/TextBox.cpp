#include "TextBox.hpp"

TextBox::TextBox(const std::string& font_path, float x, float y, float w, float h, bool background) {
    outer_rect.setSize(sf::Vector2f(w, h));
    outer_rect.setPosition(sf::Vector2f(x, y));
    outer_rect.setFillColor(sf::Color::Black);

    inner_rect.setSize(sf::Vector2f(w, h));
    inner_rect.setPosition(sf::Vector2f(x, y));
    inner_rect.setFillColor(sf::Color::White);

    blinker.setSize(sf::Vector2f(2, h - 2));
    blinker.setPosition(sf::Vector2f(x + 2, y + 1));
    blinker.setFillColor(sf::Color::Black);

    text_size = static_cast<size_t>(h - 4);
    pos_x = x;
    pos_y = y;
    height = h;
    width = w;
    show_bg = background;

    label.setFont(font_path);
    label.setCharacterSize(text_size);
    label.setPosition(sf::Vector2f(x + 2, y - 2));
    label.setFillColor(sf::Color::Black);
}

void TextBox::setSize(float w, float h) {
    width = w;
    height = h;
    text_size = static_cast<size_t>(h - 4 - 2 * thickness);
    outer_rect.setSize(sf::Vector2f(w, h));
    inner_rect.setSize(sf::Vector2f(w - 2 * thickness, h - 2 * thickness));
    blinker.setSize(sf::Vector2f(1, h - 2 * thickness - 2));
    label.setCharacterSize(text_size);
    label.setPosition(sf::Vector2f(pos_x + thickness + 2, pos_y + thickness - 1));
}

void TextBox::setPosition(float x, float y) {
    pos_x = x;
    pos_y = y;
    outer_rect.setPosition(sf::Vector2f(x, y));
    inner_rect.setPosition(sf::Vector2f(x + thickness, y + thickness));
    blinker.setPosition(sf::Vector2f(x + thickness + 2, y + thickness + 1));
    label.setPosition(sf::Vector2f(x + thickness + 2, y + thickness - 1));
}

void TextBox::setBorder(float t) {
    thickness = t;
    text_size = static_cast<size_t>(height - 4 - 2 * thickness);
    inner_rect.setSize(sf::Vector2f(width - 2 * thickness, height - 2 * thickness));
    label.setCharacterSize(text_size);
    setPosition(pos_x, pos_y);
}

bool TextBox::isEntered() const {
    return !text_input.empty();
}

std::string TextBox::getText() const {
    return text_input;
}

void TextBox::handleEvent(const sf::Event& event) {
    if (event.is<sf::Event::TextEntered>() && is_focus) {
        auto unicode = event.getIf<sf::Event::TextEntered>()->unicode;

        if ((label.findCharacterPos(focus_char).x + label.getScale().x * text_size) < (pos_x + width)) {
            std::string str;

            if (unicode > 31 && unicode < 256) {
                str += static_cast<char>(unicode);
            }
            //TODO: impl for 3.0.0
            //else if () { // 22 = Ctrl + V
            //    str = std::move(sf::Clipboard::getString());
            //}
            //else if () { // 26 = Ctrl + Z
            //    if (cache.size() > 1) {
            //        cache.pop();
            //        label = cache.top();
            //        focus_char = label.length();
            //    }
            //    else if (!cache.empty()) {
            //        label.clear();
            //        cache = std::stack<std::string>();
            //        focus_char = 0;
            //    }
            //}

            if (!str.empty()) {
                if (focus_char == label.length())
                    label += str;
                else
                    label = label.subString(0, focus_char) + str + label.subString(focus_char, label.length() - focus_char);

                focus_char += str.length();
                cache.push(label.getString());
            }
        }
    }

    if (event.is<sf::Event::KeyPressed>() && is_focus) {
        auto code = event.getIf<sf::Event::KeyPressed>()->code;

        if (code == sf::Keyboard::Key::Backspace) {
            if (focus_char != 0) {
                label.erase(focus_char - 1, 1);
                cache.push(label.getString());

                if (focus_char > 0)
                    --focus_char;
            }
        }

        if (code == sf::Keyboard::Key::Delete) {
            if (focus_char != label.length()) {
                label.erase(focus_char, 1);
                cache.push(label.getString());
            }
        }

        if (code == sf::Keyboard::Key::Enter) {
            if (!label.empty()) {
                text_input = label.getString();
                focus_char = 0;
                label.clear();
                cache = std::stack<std::string>();
            }
        }

        if (code == sf::Keyboard::Key::Left) {
            if (focus_char > 0)
                --focus_char;
        }

        if (code == sf::Keyboard::Key::Right) {
            if (focus_char < label.length())
                ++focus_char;
        }
    }

    if (event.is<sf::Event::MouseButtonPressed>()) {
        auto mouse = event.getIf<sf::Event::MouseButtonPressed>();

        if (mouse->button == sf::Mouse::Button::Left) {
            if (!label.empty()) {
                if (char_width == 0)
                    char_width = label.findCharacterPos(1).x - label.findCharacterPos(0).x;

                focus_char = std::min(label.length(), static_cast<size_t>((mouse->position.x - pos_x) / char_width));
            }

            is_focus = (
                mouse->position.x > pos_x &&
                mouse->position.x < pos_x + width &&
                mouse->position.y > pos_y &&
                mouse->position.y < pos_y + height
            );
        }
    }
}

void TextBox::draw(sf::RenderWindow& window) {
    time += clock.restart();

    sf::Color color = blinker.getFillColor();

    if (is_focus) {
        if (time.asSeconds() > 1) {
            time = sf::Time::Zero;
            blinker.setFillColor(sf::Color(color.r, color.g, color.b, 255));
        }
        else if (time.asSeconds() > 0.5)
            blinker.setFillColor(sf::Color(color.r, color.g, color.b, 0));
    }
    else {
        blinker.setFillColor(sf::Color(color.r, color.g, color.b, 0));

        if (time.asSeconds() > 300)
            time = sf::Time::Zero;
    }

    if (focus_char == 0)
        blinker.setPosition(sf::Vector2f(pos_x + thickness + 2, pos_y + thickness + 1));
    else
        blinker.setPosition(sf::Vector2f(label.findCharacterPos(focus_char).x, pos_y + thickness + 1));

    if (show_bg) {
        window.draw(outer_rect);
        window.draw(inner_rect);
    }

    window.draw(blinker);
    window.draw(label);
}

void TextBox::setTextColor(const sf::Color& color) {
    label.setFillColor(color);
}

void TextBox::setBackgroundColor(const sf::Color& color) {
    inner_rect.setFillColor(color);
}

void TextBox::setBlinkerColor(const sf::Color& color) {
    blinker.setFillColor(color);
}

void TextBox::setBorderColor(const sf::Color& color) {
    outer_rect.setFillColor(color);
}

void TextBox::focus() {
    is_focus = true;
}