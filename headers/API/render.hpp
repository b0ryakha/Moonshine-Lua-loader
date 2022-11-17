#pragma once

#include <string>
#include <map>

#include "lua_extensions.hpp"
#include "misc_functions.hpp"

extern std::map<std::string, std::pair<sf::Sprite, sf::Texture>> sprite_buffer;

namespace lua
{
    static int render_new_sprite(lua_State* L) {
        LuaStack args(L);
        if (args.size() != 3) return 0;

        std::string path = args.get<std::string>(0);
        float w = args.get<float>(1);
        float h = args.get<float>(2);

        const std::string ID = "0x" + std::to_string(rand_number(100000000, 999999999));

        sf::Texture texture;

        if (!texture.loadFromFile(path)) {
            lua_pushnil(L);
            return 1;
        }

        sprite_buffer[ID] = std::make_pair(sf::Sprite(texture), texture);

        lua_pushstring(L, ID.c_str());
        
        return 1;
    }
}