#pragma once

#include "lua_extensions.hpp"
#include "API/Objects/Vector2.hpp"

#include <thread>
#include <chrono>

extern sf::RenderWindow window;
extern sf::Event main_event;
extern size_t print_offset;

namespace API
{
    static int window_close(lua_State* L) {
        window.close();
        return 0;
    }

    static int window_capture(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 1)
            throw_error("[window.capture] Incorrect number of arguments!");

        std::string path = args.get<std::string>();
        sf::Texture screenshot;

        screenshot.create(window.getSize().x, window.getSize().y);
        screenshot.update(window);

        if (!screenshot.copyToImage().saveToFile(path))
            throw_error("[window.capture] Error when saving a screenshot!");

        return 0;
    }

    static int window_clear(lua_State* L) {
        LuaStack args(L);

        if (args.empty()) {
            window.clear();
        }
        else if (args.size() == 1) {
            window.clear(args.get<LuaUserdata, Color>());
        }

        print_offset = 0;

        return 0;
    }

    static int window_display(lua_State* L) {
        window.display();
        return 0;
    }

    static int window_get_size(lua_State* L) {
        lua_push_object<Vector2>(L, {
            window.getSize().x,
            window.getSize().y
        });

        return 1;
    }

    static int window_set_size(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 2)
            throw_error("[window.set_size] Incorrect number of arguments!");

        window.setSize(sf::Vector2u(args.get<size_t>(0), args.get<size_t>(1)));

        return 0;
    }

    static int window_get_pos(lua_State* L) {
        lua_push_object<Vector2>(L, {
            window.getPosition().x,
            window.getPosition().y
        });

        return 1;
    }

    static int window_set_pos(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 2)
            throw_error("[window.set_pos] Incorrect number of arguments!");

        window.setPosition(sf::Vector2i(args.get<int>(0), args.get<int>(1)));

        return 0;
    }

    static int window_set_title(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 1)
            throw_error("[window.set_title] Incorrect number of arguments!");

        window.setTitle(args.get<std::string>());

        return 0;
    }

    static int window_set_vsync(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 1)
            throw_error("[window.set_vsync] Incorrect number of arguments!");

        window.setVerticalSyncEnabled(args.get<bool>());

        return 0;
    }

    static int window_set_frame_limit(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 1)
            throw_error("[window.set_frame_limit] Incorrect number of arguments!");

        window.setFramerateLimit(args.get<size_t>());

        return 0;
    }

    static int window_sleep(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 1)
            throw_error("[window.sleep] Incorrect number of arguments!");

        std::this_thread::sleep_for(std::chrono::milliseconds(args.get<size_t>()));

        return 0;
    }

    static int window_await(lua_State* L) {
        while (window.isOpen()) {
            if (main_event.type == sf::Event::MouseButtonPressed || main_event.type == sf::Event::KeyPressed)
                break;
        }

        return 0;
    }

    static int window_set_icon(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 1)
            throw_error("[window.set_icon] Incorrect number of arguments!");

        sf::Sprite sprite = args.get<LuaUserdata, Sprite>();
        const sf::Texture* texture = sprite.getTexture();

        window.setIcon(texture->getSize().x, texture->getSize().y, texture->copyToImage().getPixelsPtr());

        return 0;
    }
}