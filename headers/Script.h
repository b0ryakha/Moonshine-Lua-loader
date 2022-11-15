#pragma once

#include <thread>
#include <string>
#include <array>
#include <SFML/Graphics.hpp>

#include "lua_extensions.h"
#include "API.h"

extern sf::RenderWindow window;

class Script {
private:
	lua_State* lua_state = nullptr;
	std::thread* main_thread = nullptr;

	__forceinline void open_API();

public:
	Script();
	Script(const std::string& path);
	~Script();

	void open(const std::string& path);
	void close();
};