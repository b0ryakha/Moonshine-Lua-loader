#pragma once
#include <SFML/Graphics/Text.hpp>
#include <limits>

class Label final : public sf::Text {
private:
    sf::Font font;
    std::string text;

public:
    Label() = default;
    Label(const std::string& str, const std::string& font_path, size_t size);

    void setFont(const std::string& path);
    
    size_t length() const;
    bool empty() const;
    void clear();
    std::string getString() const;
    void setString(const std::string_view str);
    std::string subString(size_t off = 0U, size_t count = std::numeric_limits<size_t>::max()) const;
    std::string& erase(size_t off, size_t count);

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