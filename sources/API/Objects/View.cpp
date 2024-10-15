#include "API/Objects/View.hpp"

API::View::View(const LuaStack& args) {
    const size_t args_size = args.size();

    if (!args.empty() && args_size != 4)
        throw_error("[View:new] Incorrect number of arguments!");

    size_t x = (args_size == 4) ? args.get<size_t>() : 0;
    size_t y = (args_size == 4) ? args.get<size_t>() : 0;
    size_t w = (args_size == 4) ? args.get<size_t>() : 0;
    size_t h = (args_size == 4) ? args.get<size_t>() : 0;

    const auto conv_pos = app->mapPixelToCoords(sf::Vector2i(x, y));
    const auto conv_size = app->mapPixelToCoords(sf::Vector2i(w, h));

    reset(sf::FloatRect(conv_pos.x, conv_pos.y, conv_size.x, conv_size.y));
}