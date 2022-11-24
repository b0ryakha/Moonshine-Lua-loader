#pragma once

#include <thread>
#include <string>
#include <array>
#include <SFML/Graphics.hpp>

#include "lua_extensions.hpp"
#include "misc_functions.hpp"
#include "API.hpp"

extern sf::RenderWindow window;

class Script {
private:
	lua_State* lua_state = nullptr;
	std::thread* main_thread = nullptr;
	const char* lua_path = nullptr;

	__forceinline void open_API();

public:
	Script();
	Script(const char* path);
	~Script();

	void open(const char* path);
	void close();
};