#pragma once

#include <thread>
#include <string>
#include <array>
#include <SFML/Graphics.hpp>

#include "lua_extensions.hpp"
#include "misc_functions.hpp"

#include "API/Objects/Vector2.hpp"
#include "API/Objects/Color.hpp"
#include "API/Objects/Font.hpp"
#include "API/Objects/Sound.hpp"
#include "API/Objects/Sprite.hpp"
#include "API/Objects/View.hpp"

#include "API/cmath.hpp"
#include "API/cursor.hpp"
#include "API/file.hpp"
#include "API/global_vars.hpp"
#include "API/keyboard.hpp"
#include "API/misc.hpp"
#include "API/mouse.hpp"
#include "API/render.hpp"
#include "API/window.hpp"

extern sf::RenderWindow window;

class Script {
private:
	mutable lua_State* lua_state = nullptr;
	mutable std::thread* main_thread = nullptr;
	mutable std::string lua_path;

	__forceinline void open_API() const;

public:
	Script() = default;
	Script(const std::string& path);
	~Script();

	void open(const std::string& path) const;
	void close() const;
	bool is_open() const;
};