#pragma once

#include "lua_extensions.hpp"

#include "API/Objects/Color.hpp"
#include "API/Objects/Vector2.hpp"

#include <string>

namespace API
{
    class Sprite {
    private:
        mutable sf::Sprite self;
        sf::Texture texture;
        std::string path;

    public:
        Sprite(const LuaStack& args);
        operator sf::Sprite() const;

        std::string get_path() const;
        sf::Sprite& get_sprite();
    };

    static int Sprite_new(lua_State* L) {
        lua_newclass<Sprite>(L);

        static auto destructor = [](lua_State* L) {
            delete lua_get_object<Sprite>(L, "Sprite", 1);
            return 0;
        };

        static auto get_path = [](lua_State* L) {
            const auto self = lua_get_object<Sprite>(L, "Sprite", 1);

            lua_pushstring(L, self->get_path().c_str());
            return 1;
        };

        static auto draw = [](lua_State* L) {
            const auto self = lua_get_object<Sprite>(L, "Sprite", 1);

            window.draw(self->get_sprite());
            return 0;
        };

        static auto set_color = [](lua_State* L) {
            auto self = lua_get_object<Sprite>(L, "Sprite", 1);
            const auto color = lua_get_object<Color>(L, "Color", 2);

            self->get_sprite().setColor(*color);
            return 0;
        };

        static auto get_color = [](lua_State* L) {
            const auto self = lua_get_object<Sprite>(L, "Sprite", 1);
            sf::Color color = self->get_sprite().getColor();
            
            lua_push_object<Color_new>(L, { color.r, color.g, color.b, color.a });
            return 1;
        };

        static auto set_position = [](lua_State* L) {
            auto self = lua_get_object<Sprite>(L, "Sprite", 1);
            double x = luaL_checknumber(L, 2);
            double y = luaL_checknumber(L, 3);

            self->get_sprite().setPosition(x, y);
            return 0;
        };

        static auto get_position = [](lua_State* L) {
            const auto self = lua_get_object<Sprite>(L, "Sprite", 1);
            sf::Vector2f pos = self->get_sprite().getPosition();
            
            lua_push_object<Vector2_new>(L, { pos.x, pos.y });
            return 1;
        };

        static auto set_rotation = [](lua_State* L) {
            auto self = lua_get_object<Sprite>(L, "Sprite", 1);
            double angle = luaL_checknumber(L, 2);

            self->get_sprite().setRotation(angle);
            return 0;
        };

        static auto get_rotation = [](lua_State* L) {
            const auto self = lua_get_object<Sprite>(L, "Sprite", 1);

            lua_pushnumber(L, self->get_sprite().getRotation());
            return 1;
        };

        static auto set_scale = [](lua_State* L) {
            auto self = lua_get_object<Sprite>(L, "Sprite", 1);
            double factor_x = luaL_checknumber(L, 2);
            double factor_y = luaL_checknumber(L, 3);

            self->get_sprite().setScale(factor_x, factor_y);
            return 0;
        };

        static auto get_scale = [](lua_State* L) {
            const auto self = lua_get_object<Sprite>(L, "Sprite", 1);
            sf::Vector2f scale = self->get_sprite().getScale();

            lua_push_object<Vector2_new>(L, { scale.x, scale.y });
            return 1;
        };

        static auto set_origin = [](lua_State* L) {
            auto self = lua_get_object<Sprite>(L, "Sprite", 1);
            double x = luaL_checknumber(L, 2);
            double y = luaL_checknumber(L, 3);

            self->get_sprite().setOrigin(x, y);
            return 0;
        };

        static auto get_origin = [](lua_State* L) {
            const auto self = lua_get_object<Sprite>(L, "Sprite", 1);
            sf::Vector2f origin = self->get_sprite().getOrigin();

            lua_push_object<Vector2_new>(L, { origin.x, origin.y });
            return 1;
        };

        static auto set_size = [](lua_State* L) {
            auto self = lua_get_object<Sprite>(L, "Sprite", 1);
            double w = luaL_checknumber(L, 2);
            double h = luaL_checknumber(L, 3);

            sf::Vector2u texture_size = self->get_sprite().getTexture()->getSize();

            self->get_sprite().setScale(w / texture_size.x, h / texture_size.y);

            return 0;
        };

        static auto get_size = [](lua_State* L) {
            const auto self = lua_get_object<Sprite>(L, "Sprite", 1);
            double w = self->get_sprite().getGlobalBounds().width;
            double h = self->get_sprite().getGlobalBounds().height;

            lua_push_object<Vector2_new>(L, { w, h });
            return 1;
        };

        static auto rotate = [](lua_State* L) {
            auto self = lua_get_object<Sprite>(L, "Sprite", 1);
            double angle = luaL_checknumber(L, 2);

            self->get_sprite().rotate(angle);
            return 0;
        };

        static auto scale = [](lua_State* L) {
            auto self = lua_get_object<Sprite>(L, "Sprite", 1);
            double factor_x = luaL_checknumber(L, 2);
            double factor_y = luaL_checknumber(L, 3);

            self->get_sprite().scale(factor_x, factor_y);
            return 0;
        };

        static auto move = [](lua_State* L) {
            auto self = lua_get_object<Sprite>(L, "Sprite", 1);
            double x_offset = luaL_checknumber(L, 2);
            double y_offset = luaL_checknumber(L, 3);

            self->get_sprite().move(x_offset, y_offset);
            return 0;
        };

        static auto copy = [](lua_State* L) {
            const auto self = lua_get_object<Sprite>(L, "Sprite", 1);

            sf::IntRect rect = self->get_sprite().getTextureRect();
            size_t t_x = rect.left;
            size_t t_y = rect.top;
            size_t t_w = rect.width;
            size_t t_h = rect.height;
            float w = self->get_sprite().getScale().x * t_w;
            float h = self->get_sprite().getScale().y * t_h;

            lua_push_object<Sprite_new>(L, { self->get_path(), w, h, t_x, t_y, t_w, t_h });
            return 1;
        };

        static auto index_get = [](lua_State* L) {
            const auto self = lua_get_object<Sprite>(L, "Sprite", 1);

            if (lua_isstring(L, 2)) {
                const std::string_view key = luaL_checkstring(L, 2);

                if (key == "get_path") lua_pushcfunction(L, get_path);
                else if (key == "draw") lua_pushcfunction(L, draw);
                else if (key == "set_color") lua_pushcfunction(L, set_color);
                else if (key == "get_color") lua_pushcfunction(L, get_color);
                else if (key == "set_position") lua_pushcfunction(L, set_position);
                else if (key == "get_position") lua_pushcfunction(L, get_position);
                else if (key == "set_rotation") lua_pushcfunction(L, set_rotation);
                else if (key == "get_rotation") lua_pushcfunction(L, get_rotation);
                else if (key == "set_scale") lua_pushcfunction(L, set_scale);
                else if (key == "get_scale") lua_pushcfunction(L, get_scale);
                else if (key == "set_origin") lua_pushcfunction(L, set_origin);
                else if (key == "get_origin") lua_pushcfunction(L, get_origin);
                else if (key == "set_size") lua_pushcfunction(L, set_size);
                else if (key == "get_size") lua_pushcfunction(L, get_size);
                else if (key == "scale") lua_pushcfunction(L, scale);
                else if (key == "rotate") lua_pushcfunction(L, rotate);
                else if (key == "move") lua_pushcfunction(L, move);
                else if (key == "copy") lua_pushcfunction(L, copy);
                else lua_pushnil(L);
            }
            else {
                lua_pushnil(L);
            }

            return 1;
        };

        static auto to_string = [](lua_State* L) {
            const auto self = lua_get_object<Sprite>(L, "Sprite", 1);
            sf::Vector2f pos = self->get_sprite().getPosition();

            std::string result;
            result = "{ \"" + self->get_path() + "\", x: " + number_to_str(pos.x) + ", y: " + number_to_str(pos.y) + " }";

            lua_pushstring(L, result.c_str());
            return 1;
        };

        static auto is_equal = [](lua_State* L) {
            const auto self = lua_get_object<Sprite>(L, "Sprite", 1);
            const auto target = lua_get_object<Sprite>(L, "Sprite", 2);

            sf::Sprite sprite = self->get_sprite();

            lua_pushboolean(L, (
                (self->get_path() == target->get_path()) &&
                (sprite.getPosition() == sprite.getPosition()) &&
                (sprite.getTexture() == sprite.getTexture()) &&
                (sprite.getTextureRect() == sprite.getTextureRect()) &&
                (sprite.getColor() == sprite.getColor()))
            );
            return 1;
        };

        lua_setmethods(L, "Sprite", {
            { "__gc", destructor },
            { "__index", index_get },
            { "__tostring", to_string },
            { "__eq", is_equal }
        });

        return 1;
    }

    static int Sprite_reg(lua_State* L) {
        LuaStack tmp(L);
        lua_remove(L, -static_cast<int>(tmp.size()));

        return Sprite_new(L);
    }
}