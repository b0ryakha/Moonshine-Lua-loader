#pragma once

#include <thread>
#include <chrono>
#include <string>
#include <array>
#include <SFML/Graphics.hpp>

#include "lua_extensions.h"
#include "API.hpp"

extern sf::RenderWindow window;

class Script {
private:
	lua_State* lua_state = nullptr;
	std::thread* main_thread = nullptr;

	__forceinline void open_API();
	__forceinline void throw_exception(const std::string& exception, bool without_closure = false) const;

public:
	Script();
	Script(const std::string& path);
	~Script();

	void open(const std::string& path);
	void close();
};