#pragma once

#include "lua_extensions.hpp"
#include <sstream>

namespace API
{
    static int color_new(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 1 && args.size() != 3 && args.size() != 4)
            throw_error("[color.new] Incorrect number of arguments!");
        
        size_t r = (args.size() > 1) ? args.get<size_t>() : 0;
        size_t g = (args.size() > 1) ? args.get<size_t>() : 0;
        size_t b = (args.size() > 1) ? args.get<size_t>() : 0;
        size_t a = (args.size() == 4) ? args.get<size_t>() : 255;
        
        if (args.size() == 1) {
            std::string tmp = args.get<std::string>(0);

            if ((tmp.length() != 7 && tmp.length() != 9) || tmp[0] != '#')
                throw_error("[color.new] Incorrect number of arguments!");

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
            a = (tmp.length() == 9 ? hex_to_number(tmp.substr(7, 2)) : 255);
        }

        if (r > 255) r = 255;
        if (g > 255) g = 255;
        if (b > 255) b = 255;
        if (a > 255) a = 255;

        lua_pushtable(L, {
            std::make_pair("r", r),
            std::make_pair("g", g),
            std::make_pair("b", b),
            std::make_pair("a", a),
        });

        return 1;
    }

    static int color_unpack(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 1)
            throw_error("[color.unpack] Incorrect number of arguments!");

        sf::Color color = lua_getcolor(args);

        lua_pushnumber(L, color.r);
        lua_pushnumber(L, color.g);
        lua_pushnumber(L, color.b);
        lua_pushnumber(L, color.a);
        return 4;
    }

    static int color_to_hex(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 1)
            throw_error("[color.to_hex] Incorrect number of arguments!");

        sf::Color color = lua_getcolor(args);
        std::stringstream ss;

        ss << '#' << std::hex << (color.r << 24 | color.g << 16 | color.b << 8 | color.a);

        lua_pushstring(L, ss.str().c_str());
        return 1;
    }
}