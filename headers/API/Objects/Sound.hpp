#pragma once

#include "lua_extensions.hpp"

#include <SFML/Audio.hpp>
#include <string>

namespace API
{
    class Sound final {
    private:
        mutable sf::Sound self;
        sf::SoundBuffer buffer;
        std::string path;

    public:
        Sound(const LuaStack& args);
        operator sf::Sound() const;
        
        std::string get_path() const;

        size_t get_volume() const;
        void set_volume(int volume);

        bool get_loop() const;
        void set_loop(bool is_repeat);

        void play(bool is_reset = false);
        void stop();
    };

    static int Sound_new(lua_State* L) {
        lua_newclass<Sound>(L);

        static auto destructor = [](lua_State* L) {
            delete lua_get_object<Sound>(L, "Sound", 1);
            return 0;
        };

        static auto get_path = [](lua_State* L) {
            const auto self = lua_get_object<Sound>(L, "Sound", 1);

            lua_pushstring(L, self->get_path().c_str());
            return 1;
        };

        static auto get_volume = [](lua_State* L) {
            const auto self = lua_get_object<Sound>(L, "Sound", 1);

            lua_pushinteger(L, self->get_volume());
            return 1;
        };

        static auto set_volume = [](lua_State* L) {
            const auto self = lua_get_object<Sound>(L, "Sound", 1);
            int volume = luaL_checkinteger(L, 2);

            self->set_volume(volume);
            return 0;
        };

        static auto get_loop = [](lua_State* L) {
            const auto self = lua_get_object<Sound>(L, "Sound", 1);

            lua_pushboolean(L, self->get_loop());
            return 1;
        };

        static auto set_loop = [](lua_State* L) {
            const auto self = lua_get_object<Sound>(L, "Sound", 1);
            bool is_repeat = lua_toboolean(L, 2);

            self->set_loop(is_repeat);
            return 0;
        };

        static auto play = [](lua_State* L) {
            const auto self = lua_get_object<Sound>(L, "Sound", 1);

            self->play();
            return 0;
        };

        static auto stop = [](lua_State* L) {
            const auto self = lua_get_object<Sound>(L, "Sound", 1);

            self->stop();
            return 0;
        };

        static auto copy = [](lua_State* L) {
            const auto self = lua_get_object<Sound>(L, "Sound", 1);

            lua_push_object<Sound_new>(L, { self->get_path(), self->get_volume(), self->get_loop() });
            return 1;
        };

        static auto index_get = [](lua_State* L) {
            const auto self = lua_get_object<Sound>(L, "Sound", 1);

            if (lua_isstring(L, 2)) {
                const std::string_view key = luaL_checkstring(L, 2);

                if (key == "get_path") lua_pushcfunction(L, get_path);
                else if (key == "get_volume") lua_pushcfunction(L, get_volume);
                else if (key == "set_volume") lua_pushcfunction(L, set_volume);
                else if (key == "get_loop") lua_pushcfunction(L, get_loop);
                else if (key == "set_loop") lua_pushcfunction(L, set_loop);
                else if (key == "play") lua_pushcfunction(L, play);
                else if (key == "stop") lua_pushcfunction(L, stop);
                else if (key == "copy") lua_pushcfunction(L, copy);
                else lua_pushnil(L);
            }
            else {
                lua_pushnil(L);
            }

            return 1;
        };

        static auto to_string = [](lua_State* L) {
            const auto self = lua_get_object<Sound>(L, "Sound", 1);

            std::string result;
            result = "{ \"" + self->get_path() + "\", " + std::to_string(self->get_volume()) + "%, " + (self->get_loop() ? "true }" : "false }");

            lua_pushstring(L, result.c_str());
            return 1;
        };

        static auto is_equal = [](lua_State* L) {
            const auto self = lua_get_object<Sound>(L, "Sound", 1);
            const auto target = lua_get_object<Sound>(L, "Sound", 2);

            lua_pushboolean(L, (
                (self->get_path() == target->get_path()) &&
                (self->get_volume() == target->get_volume()) &&
                (self->get_path() == target->get_path()))
            );
            return 1;
        };

        lua_setmethods(L, "Sound", {
            { "__gc", destructor },
            { "__index", index_get },
            { "__tostring", to_string },
            { "__eq", is_equal }
        });

        return 1;
    }

    static int Sound_reg(lua_State* L) {
        LuaStack tmp(L);
        lua_remove(L, -static_cast<int>(tmp.size()));

        return Sound_new(L);
    }
}