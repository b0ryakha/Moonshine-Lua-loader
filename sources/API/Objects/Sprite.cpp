#include "API/Objects/Sprite.hpp"

#include "Application.hpp"

#include <filesystem>
namespace fs = std::filesystem;

API::Sprite::Sprite(const LuaStack& args)
    : sf::Sprite((const sf::Texture&)sf::Texture())
{
    const size_t args_size = args.size();

    if (args_size != 3 && args_size != 7)
        throw_error("[Sprite:new] Incorrect number of arguments!");

    path = args.get<std::string>();
    int w = args.get<int>();
    int h = args.get<int>();
    int t_x = (args_size == 7 ? args.get<size_t>() : 0);
    int t_y = (args_size == 7 ? args.get<size_t>() : 0);
    int t_w = (args_size == 7 ? args.get<size_t>() : 0);
    int t_h = (args_size == 7 ? args.get<size_t>() : 0);

    if (!fs::exists(path) || !texture.loadFromFile(path))
        throw_error("[Sprite:new] Texture by path '" + path + "' cannot be loaded, check the path!");

    if (args_size == 3) {
        t_w = texture.getSize().x;
        t_h = texture.getSize().y;
    }
    else {
        setTextureRect(sf::IntRect({t_x, t_y}, {t_w, t_h}));
    }

    const auto converted = Application::instance()->mapPixelToCoords(sf::Vector2i(w, h));

    setTexture(texture);
    setScale(sf::Vector2f(converted.x / t_w, converted.y / t_h));
}

const std::string API::Sprite::get_path() const {
    return path;
}