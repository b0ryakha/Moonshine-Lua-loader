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
	mutable lua_State* lua_state = nullptr;
	mutable std::thread* main_thread = nullptr;
	mutable std::string lua_path;

	__forceinline void open_API() const;

public:
	Script() = default;
	Script(const char* path);
	~Script();

	void open(const std::string& path) const;
	void close() const;
	bool is_open() const;
};