#pragma once

#include "lua_extensions.h"
#include <SFML/Graphics.hpp>

extern sf::RenderWindow window;

namespace lua
{
	static size_t offset_y = 0;
	int print(lua_State* L);
}