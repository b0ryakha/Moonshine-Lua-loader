#pragma once

#include "lua_helper.hpp"
#include "misc_functions.hpp"

#include <random>

namespace API
{
    static std::random_device rd;
    static std::mt19937 gen{ rd() };

    namespace detail {
        static size_t number_len(double n) {
            constexpr auto epsilon = 1E-3;
            size_t result = std::ceil(std::log10(std::floor(n) + 1));
            n -= std::round(n);

            while (std::fabs(n) >= epsilon) {
                n *= 10;
                ++result;
                n -= std::round(n);
            }

            return result;
        }
    }

    static int rand_int(lua_State* L) {
        LuaStack args(L, "cmath.rand_int");

        if (args.size() != 2)
            args.error("Incorrect number of arguments!");

        const int min = args.get<int>();
        const int max = args.get<int>();

        std::uniform_int_distribution dist{ min, max };

        lua_pushinteger(L, dist(gen));
        return 1;
    }

    static int rand_double(lua_State* L) {
        LuaStack args(L, "cmath.rand_double");

        if (args.size() != 2)
            args.error("Incorrect number of arguments!");

        const double min = args.get<double>();
        const double max = args.get<double>();

        int n = std::pow(10, std::max(detail::number_len(min), detail::number_len(max) - 3));
        std::uniform_real_distribution dist{ min, max };

        lua_pushnumber(L, std::round(dist(gen) * n) / n);
        return 1;
    }

    static int lerp(lua_State* L) {
        LuaStack args(L, "cmath.lerp");

        if (args.size() != 3)
            args.error("Incorrect number of arguments!");

        const float start = args.get<float>();
        const float end = args.get<float>();
        const float time = args.get<float>();

        lua_pushnumber(L, (start + time * (end - start)));
        return 1;
    }

    static int clamp(lua_State* L) {
        LuaStack args(L, "cmath.clamp");

        if (args.size() != 3)
            args.error("Incorrect number of arguments!");

        const float number = args.get<float>();
        const float lower = args.get<float>();
        const float upper = args.get<float>();
        
        lua_pushnumber(L, std::clamp(number, lower, upper));
        return 1;
    }

    static int round(lua_State* L) {
        LuaStack args(L, "cmath.round");

        if (args.size() != 1)
            args.error("Incorrect number of arguments!");

        const float number = args.get<float>();

        lua_pushinteger(L, std::round(number));
        return 1;
    }
}