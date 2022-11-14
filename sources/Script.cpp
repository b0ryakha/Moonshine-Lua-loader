#include "Script.h"

Script::Script(sf::RenderWindow& window, const std::string& path) {
    lua_state = luaL_newstate();

    if (lua_state == 0) {
        // Failed to create Lua state
        return;
    }

    luaL_openlibs(lua_state);
    open_API();

    window.setActive(false);

    main_thread = new std::thread([&] {
        window.setActive(true);

        if (luaL_dofile(lua_state, path.c_str()) != 0) {
            // Failed to load script
        }
        else {
            lua_pcall(lua_state, 0, 0, 0);
        }

        window.setActive(false);
    });

    main_thread->detach();
}

Script::~Script() {
	delete main_thread;
	main_thread = nullptr;

    lua_close(lua_state);
}

void Script::open_API() {

}