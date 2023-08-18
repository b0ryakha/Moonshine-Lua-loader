#pragma once

#include "lua_extensions.hpp"

#include <string>
#include <sstream>

namespace API
{
    class Font final : public sf::Font {
    private:
        size_t size = 0;

    public:
        Font(const LuaStack& args);
        size_t get_size() const;

        static int push_to_lua(lua_State* L) {
            lua_newclass<Font>(L);

            static auto destructor = [](lua_State* L) {
                delete lua_get_object<Font>(L, "Font", 1);
                return 0;
            };

            static auto get_family = [](lua_State* L) {
                const auto self = lua_get_object<Font>(L, "Font", 1);

                lua_pushstring(L, self->getInfo().family.c_str());
                return 1;
            };

            static auto get_size = [](lua_State* L) {
                const auto self = lua_get_object<Font>(L, "Font", 1);

                lua_pushstring(L, std::to_string(self->get_size()).c_str());
                return 1;
            };

            static auto copy = [](lua_State* L) {
                const auto self = lua_get_object<Font>(L, "Font", 1);

                lua_push_object<Font>(L, { self->getInfo().family, self->get_size() });
                return 1;
            };

            static auto index_get = [](lua_State* L) {
                const auto self = lua_get_object<Font>(L, "Font", 1);

                if (lua_isstring(L, 2)) {
                    const std::string_view key = luaL_checkstring(L, 2);

                    if (key == "get_family") lua_pushcfunction(L, get_family);
                    else if (key == "get_size") lua_pushcfunction(L, get_size);
                    else if (key == "copy") lua_pushcfunction(L, copy);
                    else lua_pushnil(L);
                }
                else {
                    lua_pushnil(L);
                }

                return 1;
            };

            static auto to_string = [](lua_State* L) {
                const auto self = lua_get_object<Font>(L, "Font", 1);

                std::stringstream result;
                result << "{ " << self->getInfo().family << ", " << self->get_size() << " }";

                lua_pushstring(L, result.str().c_str());
                return 1;
            };

            static auto is_equal = [](lua_State* L) {
                const auto self = lua_get_object<Font>(L, "Font", 1);
                const auto target = lua_get_object<Font>(L, "Font", 2);

                lua_pushboolean(L, (
                    self->getInfo().family == target->getInfo().family &&
                    self->get_size() == target->get_size()
                ));

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

        static int reg(lua_State* L) {
            LuaStack tmp(L);
            lua_remove(L, -static_cast<int>(tmp.size()));

            return push_to_lua(L);
        }
    };
}