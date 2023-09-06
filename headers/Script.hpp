#pragma once

#include <thread>
#include <string>
#include <array>
#include <memory>
#include <SFML/Graphics.hpp>

#include "lua_helper.hpp"
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
#include "API/network.hpp"

extern sf::RenderWindow window;

class Script final {
private:
	lua_State* lua_state = nullptr;
	std::unique_ptr<std::thread> main_thread;
	std::string lua_path;

	void open_API();

public:
	Script() = default;
	Script(std::string_view path);

	void open(std::string_view path);
	bool is_open() const;
};