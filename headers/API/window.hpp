#pragma once

#include <thread>
#include <chrono>

#include "lua_extensions.hpp"
#include "API/Objects/Vector2.hpp"

extern sf::RenderWindow window;
extern sf::Event main_event;
extern size_t print_offset;

namespace API
{
    static int window_close(lua_State* L) {
        window.close();
        return 0;
    }

    /*static int window_capture(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 1 && args.size() != 5)
            throw_error("Incorrect number of arguments!");

        std::string path = args.get<std::string>();

        if (args.size() == 1) {
            sf::Texture texture;
            texture.create(window.getSize().x, window.getSize().y);

            texture.update(window);

            if (!texture.copyToImage().saveToFile(path))
                throw_error("Error when saving a screenshot!");
        }
        else {
            size_t x = args.get<size_t>();
            size_t y = args.get<size_t>();
            size_t w = args.get<size_t>();
            size_t h = args.get<size_t>();
            sf::Texture texture;
            sf::Image image;
            image.create(window.getSize().x, window.getSize().y);

            for (int i = 0; i < window.getSize().x * window.getSize().y; ++i) {
                float x = i % window.getSize().x;
                float y = i / window.getSize().x;

                image.setPixel(x, y, image.getPixel(x, y));
            }

            image.flipVertically();

            if (!image.saveToFile(path))
                throw_error("Error when saving a screenshot!");
        }

        return 0;
    }*/

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
        lua_push_object<Vector2_new>(L, {
            window.getSize().x,
            window.getSize().y
        });

        return 1;
    }

    static int window_set_size(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 2)
            throw_error("Incorrect number of arguments!");

        window.setSize(sf::Vector2u(args.get<size_t>(0), args.get<size_t>(1)));

        return 0;
    }

    static int window_get_pos(lua_State* L) {
        lua_push_object<Vector2_new>(L, {
            window.getPosition().x,
            window.getPosition().y
        });

        return 1;
    }

    static int window_set_pos(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 2)
            throw_error("Incorrect number of arguments!");

        window.setPosition(sf::Vector2i(args.get<int>(0), args.get<int>(1)));

        return 0;
    }

    static int window_set_title(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 1)
            throw_error("Incorrect number of arguments!");

        window.setTitle(args.get<std::string>());

        return 0;
    }

    static int window_set_vsync(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 1)
            throw_error("Incorrect number of arguments!");

        window.setVerticalSyncEnabled(args.get<bool>());

        return 0;
    }

    static int window_set_frame_limit(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 1)
            throw_error("Incorrect number of arguments!");

        window.setFramerateLimit(args.get<size_t>());

        return 0;
    }

    static int window_sleep(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 1)
            throw_error("Incorrect number of arguments!");

        std::this_thread::sleep_for(std::chrono::milliseconds(args.get<size_t>()));

        return 0;
    }

    static int window_await(lua_State* L) {
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

    static int window_set_icon(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 1)
            throw_error("Incorrect number of arguments!");

        std::string sprite_id = args.get<std::string>();
        sf::Texture* texture = nullptr;

        try {
            texture = &sprite_buffer[sprite_id].second;
        }
        catch (const std::out_of_range& exception) {
            throw_error(exception.what());
        }

        window.setIcon(texture->getSize().x, texture->getSize().y, texture->copyToImage().getPixelsPtr());

        return 0;
    }
}