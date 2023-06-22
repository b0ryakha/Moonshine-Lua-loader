#include "Label.hpp"

Label::Label(const std::string& str, const std::string& font_path, size_t size) : text(str) {
    setFont(font_path);
    setString(text);
    setCharacterSize(size);
}

void Label::setFont(const std::string& path) {
    if (!font.loadFromFile(path))
        throw_error("Failed to create the font face.");

    sf::Text::setFont(font);
}

std::string& Label::operator+=(const char ch) {
    text += ch;
    this->setString(text);

    return text;
}

std::string Label::operator+(const char ch) {
    std::string tmp(*this);
    tmp += ch;

    return tmp;
}

std::string& Label::operator+=(const std::string& str) {
    text += str;
    this->setString(text);

    return text;
}

std::string Label::operator+(const std::string& str) {
    std::string tmp(*this);
    tmp += str;

    return tmp;
}

Label::operator const char*() const {
    return text.c_str();
}

Label::operator const std::string() const {
    return text;
}

Label::operator const std::string_view() const {
    return text;
}