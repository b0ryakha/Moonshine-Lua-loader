#pragma once

#include <thread>
#include <string>
#include <memory>

#include "lua_helper.hpp"

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