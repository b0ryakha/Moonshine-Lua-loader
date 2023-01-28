#pragma once

#include "lua_extensions.hpp"

#include <string>
#include <unordered_map>

namespace API
{
    static std::unordered_map<std::string, sf::View> view_buffer;

    static int view_new(lua_State* L) {
        LuaStack args(L);

        if (!args.empty() && args.size() != 4)
            throw_error("[view.new] Incorrect number of arguments!");

        float x = (args.size() == 4) ? args.get<float>() : 0;
        float y = (args.size() == 4) ? args.get<float>() : 0;
        float w = (args.size() == 4) ? args.get<float>() : 0;
        float h = (args.size() == 4) ? args.get<float>() : 0;

        const std::string ID = "0x118105101119" + std::to_string(view_buffer.size());

        sf::View view;

        if (args.size() == 4)
            view.reset(sf::FloatRect(x, y, w, h));

        view_buffer[ID] = std::move(view);

        lua_pushstring(L, ID.c_str());
        return 1;
    }

    static int view_active(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 1)
            throw_error("Incorrect number of arguments!");

        std::string view_id = args.get<std::string>();

        try {
            window.setView(view_buffer[view_id]);
        }
        catch (const std::out_of_range& exception) {
            throw_error(exception.what());
        }

        return 0;
    }

    static int view_set_port(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 5)
            throw_error("Incorrect number of arguments!");

        std::string view_id = args.get<std::string>();
        float x = args.get<float>();
        float y = args.get<float>();
        float w = args.get<float>();
        float h = args.get<float>();

        try {
            view_buffer[view_id].setViewport(sf::FloatRect(x / window.getSize().x, y / window.getSize().y, w / window.getSize().x, h / window.getSize().y));
        }
        catch (const std::out_of_range& exception) {
            throw_error(exception.what());
        }

        return 0;
    }

    static int view_set_center(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 3)
            throw_error("Incorrect number of arguments!");

        std::string view_id = args.get<std::string>();
        float x = args.get<float>();
        float y = args.get<float>();

        try {
            view_buffer[view_id].setCenter(sf::Vector2f(x, y));
        }
        catch (const std::out_of_range& exception) {
            throw_error(exception.what());
        }

        return 0;
    }

    static int view_get_size(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 1)
            throw_error("Incorrect number of arguments!");

        std::string view_id = args.get<std::string>();

        try {
            lua_push_object<Vector2>(L, {
                view_buffer[view_id].getSize().x,
                view_buffer[view_id].getSize().y
            });

            return 1;
        }
        catch (const std::out_of_range& exception) {
            throw_error(exception.what());
        }
    }

    static int view_set_size(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 3)
            throw_error("Incorrect number of arguments!");

        std::string view_id = args.get<std::string>();
        float w = args.get<float>();
        float h = args.get<float>();

        try {
            view_buffer[view_id].setSize(sf::Vector2f(w, h));
        }
        catch (const std::out_of_range& exception) {
            throw_error(exception.what());
        }

        return 0;
    }

    static int view_set_zoom(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 2)
            throw_error("Incorrect number of arguments!");

        std::string view_id = args.get<std::string>();
        float zoom_factor = args.get<float>();

        try {
            view_buffer[view_id].zoom((100.f - zoom_factor) / 100.f);
        }
        catch (const std::out_of_range& exception) {
            throw_error(exception.what());
        }

        return 0;
    }

    static int view_get_rotation(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 1)
            throw_error("Incorrect number of arguments!");

        std::string view_id = args.get<std::string>();

        try {
            lua_pushnumber(L, view_buffer[view_id].getRotation());
            return 1;
        }
        catch (const std::out_of_range& exception) {
            throw_error(exception.what());
        }
    }

    static int view_set_rotation(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 2)
            throw_error("Incorrect number of arguments!");

        std::string view_id = args.get<std::string>();
        float angle = args.get<float>();

        try {
            view_buffer[view_id].setRotation(angle);
        }
        catch (const std::out_of_range& exception) {
            throw_error(exception.what());
        }

        return 0;
    }
}