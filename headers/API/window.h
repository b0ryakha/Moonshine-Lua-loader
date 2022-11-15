#pragma once

#include "lua_extensions.h"

extern sf::RenderWindow window;

namespace lua
{
	int close(lua_State* L);
	int clear(lua_State* L);
	int refresh(lua_State* L);
}