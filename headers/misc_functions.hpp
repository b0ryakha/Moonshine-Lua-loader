#pragma once

#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>

extern sf::RenderWindow window;
extern sf::Event main_event;
extern std::string FONTS_PATH;

void throw_error(const std::string& error) noexcept;