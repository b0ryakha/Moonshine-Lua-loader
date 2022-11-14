#pragma once

#include <thread>
#include <string>
#include <SFML/Graphics.hpp>

extern "C" {
	#include "lua.hpp"
	#pragma comment(lib, "lua54.lib")
}

class Script {
private:
	lua_State* lua_state = nullptr;
	std::thread* main_thread = nullptr;

	void open_API();
public:
	Script(sf::RenderWindow& window, const std::string& path);
	~Script();

};