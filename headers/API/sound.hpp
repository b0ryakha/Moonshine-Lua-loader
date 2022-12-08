#pragma once

#include "lua_extensions.hpp"

#include <SFML/Audio.hpp>
#include <string>
#include <unordered_map>

namespace API
{
    static std::unordered_map<std::string, std::pair<sf::Sound, sf::SoundBuffer>> sound_buffer;

    static int sound_new(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 2 && args.size() != 3) {
            lua_pushnil(L);
            return 1;
        }

        std::string path = args.get<std::string>();
        size_t volume = args.get<size_t>();
        bool is_repeat = (args.size() == 3) ? args.get<bool>() : false;

        const std::string ID = "0x115111117110100" + std::to_string(sound_buffer.size());

        sf::SoundBuffer buffer;
        if (!buffer.loadFromFile(path)) {
            lua_pushnil(L);
            return 1;
        }
        
        sf::Sound sound(buffer);

        sound.setLoop(is_repeat);
        sound.setVolume((volume > 100) ? 100 : volume);

        sound_buffer[ID] = std::make_pair(sound, buffer);
        
        lua_pushstring(L, ID.c_str());
        return 1;
    }

    static int sound_play(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 1 && args.size() != 2)
            throw_error("Incorrect number of arguments!");

        std::string sound_id = args.get<std::string>();
        bool is_reset = (args.size() == 2) ? args.get<bool>() : false;

        sf::Sound* sound = nullptr;
        sf::SoundBuffer* buffer = nullptr;

        try {
            sound = &sound_buffer[sound_id].first;
            buffer = &sound_buffer[sound_id].second;
        }
        catch (const std::out_of_range& exception) {
            throw_error(exception.what());
        }
        
        if (is_reset || sound->getStatus() != sf::SoundSource::Status::Playing) {
            sound->setBuffer(*buffer);
            sound->play();
        }

        return 0;
    }

    static int sound_stop(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 1)
            throw_error("Incorrect number of arguments!");

        std::string sound_id = args.get<std::string>();

        try {
            sound_buffer[sound_id].first.stop();
        }
        catch (const std::out_of_range& exception) {
            throw_error(exception.what());
        }

        return 0;
    }

    static int sound_set_volume(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 2)
            throw_error("Incorrect number of arguments!");

        std::string sound_id = args.get<std::string>();
        size_t volume = args.get<size_t>();

        try {
            sound_buffer[sound_id].first.setVolume((volume > 100) ? 100 : volume);
        }
        catch (const std::out_of_range& exception) {
            throw_error(exception.what());
        }

        return 0;
    }

    static int sound_set_loop(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 2)
            throw_error("Incorrect number of arguments!");

        std::string sound_id = args.get<std::string>();
        bool is_repeat = args.get<bool>();

        try {
            sound_buffer[sound_id].first.setLoop(is_repeat);
        }
        catch (const std::out_of_range& exception) {
            throw_error(exception.what());
        }

        return 0;
    }
}