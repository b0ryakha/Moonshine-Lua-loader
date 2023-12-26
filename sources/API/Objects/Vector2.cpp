#include "API/Objects/Vector2.hpp"

API::Vector2::Vector2(const LuaStack& args) {
    if (args.size() != 2)
        throw_error("[Vector2:new] Incorrect number of arguments!");

    x = args.get<double>();
    y = args.get<double>();
}