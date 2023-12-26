#include "API/Objects/Color.hpp"

API::Color::Color(const LuaStack& args) : sf::Color(0, 0, 0) {
    if (args.size() != 1 && args.size() != 3 && args.size() != 4)
        throw_error("[Color:new] Incorrect number of arguments!");

    if (args.size() > 1) {
        r = std::min(std::max(args.get<int>(), 0), 255);
        g = std::min(std::max(args.get<int>(), 0), 255);
        b = std::min(std::max(args.get<int>(), 0), 255);
    }

    if (args.size() == 4)
        a = std::min(std::max(args.get<int>(), 0), 255);

    if (args.size() == 1) {
        std::string hex = args.get<std::string>();

        if (hex.empty() || hex[0] != '#' || (hex.length() != 7 && hex.length() != 9))
            throw_error("[Color:new] Incorrect hex format!");

        if (hex.length() != 9)
            hex += "FF";

        if (std::sscanf(hex.c_str(), "#%02x%02x%02x%02x", (uint_t*)&r, (uint_t*)&g, (uint_t*)&b, (uint_t*)&a) != 4)
            throw_error("[Color:new] Converting hex error!");
    }
}