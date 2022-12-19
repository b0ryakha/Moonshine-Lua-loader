#include "API/Objects/Color.hpp"

API::Color::Color(const LuaStack& args) {
    if (args.size() != 1 && args.size() != 3 && args.size() != 4)
        throw_error("[Color.new] Incorrect number of arguments!");

    if (args.size() > 1) {
        r = args.get<size_t>();
        g = args.get<size_t>();
        b = args.get<size_t>();
    }

    if (args.size() == 4)
        a = args.get<size_t>();

    if (args.size() == 1) {
        std::string tmp = args.get<std::string>();

        if ((tmp.length() != 7 && tmp.length() != 9) || tmp[0] != '#')
            throw_error("[Color.new] Incorrect number of arguments!");

        auto hex_to_number = [](const std::string& hex) -> size_t {
            size_t result = 0;

            for (size_t i = 0; i < hex.length(); ++i) {
                char tmp = hex[hex.length() - 1 - i];
                result += static_cast<size_t>((tmp >= 'A' && tmp <= 'F') ? tmp - 'A' + 10 : tmp - '0') * pow(16, i);
            }

            return result;
        };

        r = hex_to_number(tmp.substr(1, 2));
        g = hex_to_number(tmp.substr(3, 2));
        b = hex_to_number(tmp.substr(5, 2));

        if (tmp.length() == 9)
            a = hex_to_number(tmp.substr(7, 2));
    }
}

API::Color::operator sf::Color() const {
    return sf::Color(r, g, b, a);
}