#pragma once
#include "lua_helper.hpp"

#include "API/Objects/Vector2.hpp"

#include <SFML/Graphics.hpp>
#include <sstream>

namespace API
{
    class Font final : public sf::Font {
    private:
        std::string family;
        size_t size = 0;
        ushort_t styles = sf::Text::Style::Regular;

    public:
        Font(const LuaStack& args);
        size_t get_size() const;
        sf::Text::Style get_style() const;

        static int push_to_lua(lua_State* L) {
            lhelper::new_class<Font>(L);

            static auto destructor = [](lua_State* L) {
                delete lhelper::get_object<Font>(L, "Font", 1);
                return 0;
            };

            static auto get_family = [](lua_State* L) {
                const auto self = lhelper::get_object<Font>(L, "Font", 1);

                lua_pushstring(L, self->family.c_str());
                return 1;
            };

            static auto get_size = [](lua_State* L) {
                const auto self = lhelper::get_object<Font>(L, "Font", 1);

                lua_pushinteger(L, self->get_size());
                return 1;
            };

            static auto get_style = [](lua_State* L) {
                const auto self = lhelper::get_object<Font>(L, "Font", 1);
                const ushort_t styles = self->get_style();
                std::string result;

                if ((styles & sf::Text::Style::Regular) == sf::Text::Style::Regular)
                    result.push_back('r');

                if ((styles & sf::Text::Style::Bold) == sf::Text::Style::Bold)
                    result.push_back('b');

                if ((styles & sf::Text::Style::Italic) == sf::Text::Style::Italic)
                    result.push_back('i');

                if ((styles & sf::Text::Style::Underlined) == sf::Text::Style::Underlined)
                    result.push_back('l');

                if ((styles & sf::Text::Style::StrikeThrough) == sf::Text::Style::StrikeThrough)
                    result.push_back('s');

                lua_pushstring(L, result.c_str());
                return 1;
            };

            static auto get_bounds = [](lua_State* L) {
                const auto self = lhelper::get_object<Font>(L, "Font", 1);
                const std::string_view symbol = luaL_checkstring(L, 2);

                if (symbol.empty()) {
                    lhelper::push_object<Vector2>(L, { 0, 0 });
                    return 1;
                }

                bool is_bold = (self->styles & sf::Text::Style::Bold) == sf::Text::Style::Bold;
                sf::Glyph glyph = self->getGlyph(symbol[0], self->size, is_bold);

                lhelper::push_object<Vector2>(L, {
                    glyph.advance,
                    glyph.bounds.height
                });

                return 1;
            };

            static auto copy = [](lua_State* L) {
                const auto self = lhelper::get_object<Font>(L, "Font", 1);

                lhelper::push_object<Font>(L, {
                    self->family,
                    lua_Number(self->get_size())
                });
                
                return 1;
            };

            static auto index_get = [](lua_State* L) {
                const auto self = lhelper::get_object<Font>(L, "Font", 1);

                if (lua_isstring(L, 2)) {
                    const std::string_view key = luaL_checkstring(L, 2);

                    if (key == "get_family") lua_pushcfunction(L, get_family);
                    else if (key == "get_size") lua_pushcfunction(L, get_size);
                    else if (key == "get_style") lua_pushcfunction(L, get_style);
                    else if (key == "get_bounds") lua_pushcfunction(L, get_bounds);
                    else if (key == "copy") lua_pushcfunction(L, copy);
                    else lua_pushnil(L);
                }
                else {
                    lua_pushnil(L);
                }

                return 1;
            };

            static auto to_string = [](lua_State* L) {
                const auto self = lhelper::get_object<Font>(L, "Font", 1);

                std::stringstream result;
                result << "{ " << self->family << ", " << self->get_size() << ", " << self->get_style() << " }";

                lua_pushstring(L, std::move(result).str().c_str());
                return 1;
            };

            static auto is_equal = [](lua_State* L) {
                const auto self = lhelper::get_object<Font>(L, "Font", 1);
                const auto target = lhelper::get_object<Font>(L, "Font", 2);

                lua_pushboolean(L, (
                    self->family == target->family &&
                    self->get_size() == target->get_size() &&
                    self->get_style() == target->get_style()
                ));

                return 1;
            };

            lhelper::set_methods(L, "Font", {
                { "__gc", destructor },
                { "__index", index_get },
                { "__tostring", to_string },
                { "__eq", is_equal }
            });

            return 1;
        }

        static int reg(lua_State* L) {
            LuaStack tmp(L, "Font:register");
            lua_remove(L, -static_cast<int>(tmp.size()));

            return push_to_lua(L);
        }
    };
}