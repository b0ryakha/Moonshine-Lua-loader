#pragma once

#include <thread>
#include <string>
#include <array>
#include <SFML/Graphics.hpp>

#include "lua_extensions.hpp"
#include "misc_functions.hpp"

#include "cmath.hpp"
#include "color.hpp"
#include "cursor.hpp"
#include "file.hpp"
#include "global_vars.hpp"
#include "keyboard.hpp"
#include "misc.hpp"
#include "mouse.hpp"
#include "render.hpp"
#include "sound.hpp"
#include "view.hpp"
#include "window.hpp"

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