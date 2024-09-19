#pragma once

#include "lua_helper.hpp"
#include "API/Objects/Vector2.hpp"
#include "API/Objects/Color.hpp"
#include "API/Objects/Sprite.hpp"

#include <thread>
#include <chrono>

extern sf::RenderWindow* window;
extern sf::Event* main_event;

namespace API
{
    static int window_close(lua_State* L) {
        (void) L;
        window->close();
        return 0;
    }

    static int window_is_open(lua_State* L) {
        (void) L;
        lua_pushboolean(L, window->isOpen());
        return 1;
    }

    static int window_capture(lua_State* L) {
        LuaStack args(L, "window->capture");

        if (args.size() != 1 && args.size() != 5)
            args.error("Incorrect number of arguments!");

        const std::string path = args.get<std::string>();
        size_t x = args.size() == 5 ? args.get<size_t>() : 0u;
        size_t y = args.size() == 5 ? args.get<size_t>() : 0u;
        size_t w = args.size() == 5 ? args.get<size_t>() : 0u;
        size_t h = args.size() == 5 ? args.get<size_t>() : 0u;

        sf::Texture screenshot;
        screenshot.create(window->getSize().x, window->getSize().y);
        screenshot.update(*window);

        sf::Image image = screenshot.copyToImage();

        if (args.size() == 5) {
            x = std::min(static_cast<unsigned>(x), window->getSize().x);
            y = std::min(static_cast<unsigned>(y), window->getSize().y);
            w = std::min(static_cast<unsigned>(w), window->getSize().x);
            h = std::min(static_cast<unsigned>(h), window->getSize().y);

            sf::Image cropped;
            cropped.create(w, h);

            for (size_t i = 0; i < h; ++i) {
                for (size_t j = 0; j < w; ++j) {
                    cropped.setPixel(j, i, image.getPixel(j + x, i + y));
                }
            }

            image = std::move(cropped);
        }

        if (!image.saveToFile(path))
            args.error("Attempt to save a corrupted image!");

        return 0;
    }

    static int window_clear(lua_State* L) {
        LuaStack args(L, "window->clear");

        if (args.empty()) {
            window->clear();
        }
        else if (args.size() == 1) {
            window->clear(args.get<LuaUserdata, API::Color>(0));
        }
        else {
            args.error("Incorrect number of arguments!");
        }

        return 0;
    }

    static int window_display(lua_State* L) {
        (void) L;
        window->display();
        return 0;
    }

    static int window_get_size(lua_State* L) {
        lhelper::push_object<Vector2>(L, {
            lua_Number(window->getSize().x),
            lua_Number(window->getSize().y)
        });

        return 1;
    }

    static int window_set_size(lua_State* L) {
        LuaStack args(L, "window->set_size");

        if (args.size() != 2)
            args.error("Incorrect number of arguments!");

        const size_t width = args.get<size_t>();
        const size_t height = args.get<size_t>();

        window->setSize(sf::Vector2u(width, height));

        return 0;
    }

    static int window_get_pos(lua_State* L) {
        lhelper::push_object<Vector2>(L, {
            lua_Number(window->getPosition().x),
            lua_Number(window->getPosition().y)
        });

        return 1;
    }

    static int window_set_pos(lua_State* L) {
        LuaStack args(L, "window->set_pos");

        if (args.size() != 2)
            args.error("Incorrect number of arguments!");

        window->setPosition(sf::Vector2i(args.get<int>(0), args.get<int>(1)));

        return 0;
    }

    static int window_set_title(lua_State* L) {
        LuaStack args(L, "window->set_title");

        if (args.size() != 1)
            args.error("Incorrect number of arguments!");

        window->setTitle(args.get<std::string>());

        return 0;
    }

    static int window_set_vsync(lua_State* L) {
        LuaStack args(L, "window->set_vsync");

        if (args.size() != 1)
            args.error("Incorrect number of arguments!");

        window->setVerticalSyncEnabled(args.get<bool>());

        return 0;
    }

    static int window_set_frame_limit(lua_State* L) {
        LuaStack args(L, "window->set_frame_limit");

        if (args.size() != 1)
            args.error("Incorrect number of arguments!");

        window->setFramerateLimit(args.get<size_t>());

        return 0;
    }

    static int window_sleep(lua_State* L) {
        LuaStack args(L, "window->sleep");

        if (args.size() != 1)
            args.error("Incorrect number of arguments!");

        std::this_thread::sleep_for(std::chrono::milliseconds(args.get<size_t>()));

        return 0;
    }

    static int window_await(lua_State* L) {
        (void) L;
        while (window->isOpen()) {
            if (main_event->type == sf::Event::MouseButtonPressed || main_event->type == sf::Event::KeyPressed)
                break;
        }

        return 0;
    }

    static int window_set_icon(lua_State* L) {
        LuaStack args(L, "window->set_icon");

        if (args.size() != 1)
            args.error("Incorrect number of arguments!");

        sf::Sprite sprite = args.get<LuaUserdata, API::Sprite>();
        const sf::Texture* texture = sprite.getTexture();

        window->setIcon(texture->getSize().x, texture->getSize().y, texture->copyToImage().getPixelsPtr());

        return 0;
    }
}