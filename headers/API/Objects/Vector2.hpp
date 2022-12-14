#pragma once

#include "lua_extensions.hpp"

namespace API
{
    class Vector2 {
    private:
        double x = 0;
        double y = 0;

    public:
        Vector2(const LuaStack& args);
    };

    static int Vector2_new(lua_State* L) {
        lua_newclass<Vector2>(L);

        static auto destructor = [](lua_State* L) {
            delete lua_getself<Vector2>(L, "Vector2");
            return 0;
        };

        /*static auto get_number = [](lua_State* L) {
            lua_pushnumber(L, lua_getself<Vector2>(L, "Vector2")->get_number());
            return 1;
        };*/

        lua_setmethods(L, "Vector2", {
            { "__gc", destructor },
            { nullptr, nullptr }
        });

        lua_setmetatable(L, -2);
        return 1;
    }
}