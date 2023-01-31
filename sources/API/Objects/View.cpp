#include "API/Objects/View.hpp"

API::View::View(const LuaStack& args) {
    if (!args.empty() && args.size() != 4)
        throw_error("[View:new] Incorrect number of arguments!");

    float x = (args.size() == 4) ? args.get<float>() : 0;
    float y = (args.size() == 4) ? args.get<float>() : 0;
    float w = (args.size() == 4) ? args.get<float>() : 0;
    float h = (args.size() == 4) ? args.get<float>() : 0;

    reset(sf::FloatRect(x, y, w, h));
}