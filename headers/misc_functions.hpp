#pragma once

#include <SFML/Graphics.hpp>
#include <boost/random.hpp>
#include <chrono>
#include <thread>
#include <string>

extern sf::RenderWindow window;
extern sf::Event main_event;
extern std::string FONTS_PATH;

int rand_number(int min, int max);
void throw_error(const std::string& error, bool close_window = true) noexcept;