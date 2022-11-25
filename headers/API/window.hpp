#pragma once

#include <thread>
#include <chrono>

#include "lua_extensions.hpp"

extern sf::RenderWindow window;
extern sf::Event main_event;
extern size_t print_offset;

namespace lua
{
    static int close(lua_State* L) {
        window.close();
        print_offset = 0;
        return 0;
    }

    static int clear(lua_State* L) {
        LuaStack args(L);

        if (args.empty()) {
            window.clear();
        }
        else if (args.size() == 1) {
            window.clear(lua_getcolor(args));
        }

        return 0;
    }

    static int display(lua_State* L) {
        window.display();
        return 0;
    }

    static int get_size(lua_State* L) {
        lua_pushtable(L, {
            std::make_pair("w", window.getSize().x),
            std::make_pair("h", window.getSize().y)
        });

        return 1;
    }

    static int set_size(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 2)
            throw_error("Incorrect number of arguments!");

        window.setSize(sf::Vector2u(args.get<size_t>(0), args.get<size_t>(1)));

        return 0;
    }

    static int get_pos(lua_State* L) {
        lua_pushtable(L, {
            std::make_pair("x", window.getPosition().x),
            std::make_pair("y", window.getPosition().y)
        });

        return 1;
    }

    static int set_pos(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 2)
            throw_error("Incorrect number of arguments!");

        window.setPosition(sf::Vector2i(args.get<int>(0), args.get<int>(1)));

        return 0;
    }

    static int set_title(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 1)
            throw_error("Incorrect number of arguments!");

        window.setTitle(args.get<std::string>());

        return 0;
    }

    static int set_vsync(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 1)
            throw_error("Incorrect number of arguments!");

        window.setVerticalSyncEnabled(args.get<bool>());

        return 0;
    }

    static int set_frame_limit(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 1)
            throw_error("Incorrect number of arguments!");

        window.setFramerateLimit(args.get<size_t>());

        return 0;
    }

    static int sleep(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 1)
            throw_error("Incorrect number of arguments!");

        std::this_thread::sleep_for(std::chrono::milliseconds(args.get<size_t>()));

        return 0;
    }

    static int await(lua_State* L) {
        while (window.isOpen()) {
            switch (main_event.type) {
                case sf::Event::MouseButtonPressed:
                case sf::Event::KeyPressed:
                    goto loop_break;
            }
        }
        loop_break:

        return 0;
    }
}