#pragma once

#include <string>
#include <map>

#include "lua_extensions.hpp"
#include "misc_functions.hpp"

extern std::map<std::string, std::pair<sf::Sprite, sf::Texture>> sprite_buffer;

namespace lua
{
    static int render_new_sprite(lua_State* L) {
        int arg_count = lua_gettop(L);
        if (arg_count != 3) return 0;

        float h = lua_get_value<float>(L);
        float w = lua_get_value<float>(L);
        std::string path = lua_get_value<std::string>(L);

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