#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "misc_functions.hpp"

class Label final : public sf::Text {
private:
    sf::Font font;
    std::string text;

public:
    Label() = default;
    Label(const std::string& str, const std::string& font_path, size_t size);

    void setFont(const std::string& path);
    inline bool empty() noexcept { return text.empty(); }
    inline void popBack() {
        text.pop_back();
        this->setString(text);
    }

    std::string& operator+=(const char ch);
    std::string operator+(const char ch);
    std::string& operator+=(const std::string& str);
    std::string operator+(const std::string& str);

    operator const char*() const;
    operator const std::string() const;
    operator const std::string_view() const;
};