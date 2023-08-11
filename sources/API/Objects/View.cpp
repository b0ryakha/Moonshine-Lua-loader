#include "API/Objects/View.hpp"

API::View::View(const LuaStack& args) {
    const size_t args_size = args.size();

    if (!args.empty() && args_size != 4)
        throw_error("[View:new] Incorrect number of arguments!");

    size_t x = (args_size == 4) ? args.get<size_t>() : 0;
    size_t y = (args_size == 4) ? args.get<size_t>() : 0;
    float w = (args_size == 4) ? args.get<float>() : 0.f;
    float h = (args_size == 4) ? args.get<float>() : 0.f;

    const auto converted = window.mapPixelToCoords(sf::Vector2i(x, y));

    reset(sf::FloatRect(converted.x, converted.y, w, h));
}