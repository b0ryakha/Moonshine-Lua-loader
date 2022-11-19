#include "misc_functions.hpp"

int rand_number(int min, int max) {
    boost::random::mt19937 gen{ static_cast<uint32_t>(time(0) + rand()) };
    boost::random::uniform_int_distribution<> dist{ min, max };

    return dist(gen);
}

std::string correct_font(const std::string& font) {
    if (font.length() > 4) {
        if (std::string(font.end() - 4, font.end()) != ".ttf") {
            return font + ".ttf";
        }
    }
    else {
        return font + ".ttf";
    }

    return font;
}