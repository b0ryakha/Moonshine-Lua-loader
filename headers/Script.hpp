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
	std::string lua_path;

	__forceinline void open_API();

public:
	Script() = default;
	Script(const char* path);
	~Script();

	void open(const std::string& path);
	void close();
};