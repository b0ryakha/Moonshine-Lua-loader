#include "Label.hpp"

Label::Label(const std::string& str, const std::string& font_path, size_t size) {
    setFont(font_path);
    sf::Text::setString(str);
    sf::Text::setCharacterSize(size);
}

void Label::setFont(const std::string& path) {
    if (!font.loadFromFile(path))
        throw_error("Failed to create the font face.");

    sf::Text::setFont(font);
}

size_t Label::length() const {
    return text.length();
}

bool Label::empty() const {
    return text.empty();
}

void Label::clear() {
    text.clear();
    text.shrink_to_fit();
    sf::Text::setString("");
}

std::string Label::getString() const {
    return text;
};

void Label::setString(const std::string_view str) {
    text = str;
    sf::Text::setString(text);
};

std::string Label::subString(size_t off, size_t count) const {
    return text.substr(off, count);
}

std::string& Label::erase(size_t off, size_t count) {
    auto&& tmp = text.erase(off, count);
    sf::Text::setString(tmp);
    return tmp;
}

void Label::operator=(const char ch) {
    text = ch;
    sf::Text::setString(text);
}

void Label::operator=(const char* str) {
    text = str;
    sf::Text::setString(text);
}

void Label::operator=(const std::string& str) {
    text = str;
    sf::Text::setString(text);
}

void Label::operator=(const std::string_view str) {
    text = str;
    sf::Text::setString(text);
}


std::string& Label::operator+=(const char ch) {
    text += ch;
    sf::Text::setString(text);
    return text;
}

std::string& Label::operator+=(const char* str) {
    text += str;
    sf::Text::setString(text);
    return text;
}

std::string& Label::operator+=(const std::string& str) {
    text += str;
    sf::Text::setString(text);
    return text;
}

std::string& Label::operator+=(const std::string_view str) {
    text += str;
    sf::Text::setString(text);
    return text;
}


std::string Label::operator+(const char ch) {
    return text + ch;
}

std::string Label::operator+(const char* str) {
    return text + str;
}

std::string Label::operator+(const std::string& str) {
    return text + str;
}

std::string Label::operator+(const std::string_view str) {
    return text + std::string(str);
}