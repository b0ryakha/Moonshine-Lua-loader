#pragma once

#include <thread>
#include <string>
#include <array>
#include <SFML/Graphics.hpp>

#include "lua_extensions.h"

class Script {
private:
	lua_State* lua_state = nullptr;
	std::thread* main_thread = nullptr;

	__forceinline void open_API();
public:
	Script(sf::RenderWindow& window, const std::string& path);
	~Script();

};