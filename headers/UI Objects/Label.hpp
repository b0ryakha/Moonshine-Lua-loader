#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <limits>

#include "misc_functions.hpp"

class Label final : public sf::Text {
private:
    sf::Font font;
    std::string text;

public:
    Label() = default;
    Label(const std::string& str, const std::string& font_path, size_t size);

    void setFont(const std::string& path);
    
    inline size_t length() const noexcept { return text.length(); }
    inline bool empty() const noexcept { return text.empty(); }
    inline void clear() noexcept {
        text.clear();
        text.shrink_to_fit();
        sf::Text::setString("");
    }
    inline std::string getString() const noexcept { return text; };
    inline void setString(const std::string_view str) noexcept {
        text = str;
        sf::Text::setString(text);
    };
    inline std::string subString(size_t off = 0U, size_t count = std::numeric_limits<size_t>::max()) const {
        return text.substr(off, count);
    }
    inline std::string& erase(size_t off, size_t count) {
        auto&& tmp = text.erase(off, count);
        sf::Text::setString(tmp);
        return tmp;
    }

    void operator=(const char ch);
    void operator=(const char* str);
    void operator=(const std::string& str);
    void operator=(const std::string_view str);

    std::string& operator+=(const char ch);
    std::string& operator+=(const char* str);
    std::string& operator+=(const std::string& str);
    std::string& operator+=(const std::string_view str);

    std::string operator+(const char ch);
    std::string operator+(const char* str);
    std::string operator+(const std::string& str);
    std::string operator+(const std::string_view str);
};