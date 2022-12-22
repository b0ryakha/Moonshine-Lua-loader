#pragma once

#include "lua_extensions.hpp"

#include <string>
#include <unordered_map>
#include <memory>

namespace API
{
    class Font {
    private:
        std::shared_ptr<sf::Font> self;
        std::string family;
        size_t size = 0;

    public:
        Font(const LuaStack& args);

        operator sf::Font*() const;

        size_t get_size() const;
        std::string get_family() const;
    };

    static int Font_new(lua_State* L) {
        lua_newclass<Font>(L);

        static auto destructor = [](lua_State* L) {
            delete lua_get_object<Font>(L, "Font", 1);
            return 0;
        };

        static auto get_name = [](lua_State* L) {
            const auto self = lua_get_object<Font>(L, "Font", 1);

            lua_pushstring(L, self->get_family().c_str());
            return 1;
        };

        static auto index_get = [](lua_State* L) {
            const auto self = lua_get_object<Font>(L, "Font", 1);
            
            if (lua_isstring(L, 2)) {
                const std::string_view key = luaL_checkstring(L, 2);

                if (key == "get_family") lua_pushcfunction(L, get_name);
                else lua_pushnil(L);
            }
            else {
                lua_pushnil(L);
            }

            return 1;
        };

        static auto to_string = [](lua_State* L) {
            const auto self = lua_get_object<Font>(L, "Font", 1);

            std::string result;
            result = "{ " + self->get_family() + ", " + std::to_string(self->get_size()) + " }";

            lua_pushstring(L, result.c_str());
            return 1;
        };

        static auto is_equal = [](lua_State* L) {
            const auto self = lua_get_object<Font>(L, "Font", 1);
            const auto target = lua_get_object<Font>(L, "Font", 2);

            lua_pushboolean(L, ((self->get_family() == target->get_family()) && (self->get_size() == target->get_size())));
            return 1;
        };

        lua_setmethods(L, "Font", {
            { "__gc", destructor },
            { "__index", index_get },
            { "__tostring", to_string },
            { "__eq", is_equal }
        });

        return 1;
    }

    static int Font_reg(lua_State* L) {
        LuaStack tmp(L);
        lua_remove(L, -static_cast<int>(tmp.size()));

        return Font_new(L);
    }
}