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