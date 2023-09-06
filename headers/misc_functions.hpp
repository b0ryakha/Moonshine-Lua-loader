#pragma once

#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>

using ushort_t = unsigned short;

extern sf::RenderWindow window;
extern sf::Event main_event;
extern std::string font_path;

template<typename T>
float pixel_to_coord(T pixel) {
	return window.mapPixelToCoords({ static_cast<int>(pixel), 0 }).x;
}

template<typename T>
int pixel_to_rcoord(T pixel) {
	return static_cast<int>(std::round(window.mapPixelToCoords({ static_cast<int>(pixel), 0 }).x));
}

void throw_error(std::string_view error);