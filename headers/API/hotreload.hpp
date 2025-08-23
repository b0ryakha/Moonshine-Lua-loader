#pragma once
#include "lua_helper.hpp"
#include "Application.hpp"

namespace API
{
    static LuaTable state;

    static int get_state(lua_State* L) {
        lhelper::push_table(L, state);
        return 1;
    }

    static int set_state(lua_State* L) {
        LuaStack args(L, "hotreload.set_state");

        if (args.size() != 1)
            args.error("Incorrect number of arguments!");

        const LuaTable new_state = args.get<LuaTable>();
        state = std::move(new_state);

        return 0;
    }

    static int reload(lua_State* L) {
        Application::instance()->setNeedReload();
        luaL_error(L, "");
        return 0;
    }
}