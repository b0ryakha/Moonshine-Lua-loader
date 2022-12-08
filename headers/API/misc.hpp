#pragma once

#include "lua_extensions.hpp"

extern sf::RenderWindow window;
extern std::string FONTS_PATH;
extern size_t print_offset;

namespace API
{
    struct Object {
        int number = 0;
        Object(int number): number(number) {}
    };

    static int object_new(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 1) {
            lua_pushnil(L);
            return 1;
        }

        int number = args.get<int>();
        
        *static_cast<Object**>(lua_newuserdata(L, sizeof(Object*))) = new Object(number);

        static auto destructor = [](lua_State* L) {
            delete *static_cast<Object**>(luaL_checkudata(L, 1, "Object"));
            return 0;
        };

        static auto get_number = [](lua_State* L) {
            Object* dummy = *static_cast<Object**>(luaL_checkudata(L, 1, "Object"));

            lua_pushnumber(L, dummy->number);
            return 1;
        };

        if (luaL_newmetatable(L, "Object")) {
            static const luaL_Reg functions[] = {
                { "get_number", get_number },
                { "__gc", destructor },
            };

            luaL_setfuncs(L, functions, 0);
            lua_pushvalue(L, -1);
            lua_setfield(L, -2, "__index");
        }
        
        lua_setmetatable(L, -2);
        return 1;
    }



	static int print(lua_State* L) {
        LuaStack args(L);
        std::string result;
        const size_t size = 20;

        for (size_t i = 0; i < args.size(); ++i) {
            std::string value;

            switch (args.get_type(i)) {
                case LuaMultiValueType::Number:
                    value = std::to_string(args.get<float>(i));
                    break;
                case LuaMultiValueType::String:
                    value = args.get<std::string>(i);
                    break;
                case LuaMultiValueType::Boolean:
                    value = args.get<bool>(i) ? "true" : "false";
                    break;
                default:
                    value = "nil";
            }

            result += value + '\t';
        }

        sf::Font font;
        if (!font.loadFromFile(FONTS_PATH + "arial.ttf"))
            throw_error("Failed to create the font face.");

        sf::Text text(sf::String::fromUtf8(result.begin(), result.end()), font, size);
        text.setPosition(sf::Vector2f(0, print_offset));
        text.setFillColor(sf::Color::White);

        window.draw(text);

        print_offset += size;

        if (print_offset >= window.getSize().y)
            print_offset = 0;

        return 0;
    }
}