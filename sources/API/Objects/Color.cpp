#include "API/Objects/Color.hpp"

API::Color::Color(const LuaStack& args) : sf::Color(0, 0, 0) {
    if (args.size() != 1 && args.size() != 3 && args.size() != 4)
        throw_error("[Color:new] Incorrect number of arguments!");

    if (args.size() > 1) {
        r = args.get<int>();
        g = args.get<int>();
        b = args.get<int>();
    }

    if (args.size() == 4)
        a = args.get<int>();

    if (args.size() == 1) {
        std::string hex = args.get<std::string>();

        if (hex.empty() || hex[0] != '#' || (hex.length() != 7 && hex.length() != 9))
            throw_error("[Color:new] Incorrect hex format!");

        if (hex.length() != 9)
            hex += "FF";

        if (std::sscanf(hex.c_str(), "#%02x%02x%02x%02x", &r, &g, &b, &a) != 4)
            throw_error("[Color:new] Ñonverting hex error!");
    }
}