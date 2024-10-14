#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

using ushort_t = unsigned short;
using uint_t = unsigned int;

extern sf::RenderWindow* window;
extern sf::Event* main_event;
extern std::string font_path;

template<typename T>
float pixel_to_coord(T pixel) {
	return window->mapPixelToCoords({ static_cast<int>(pixel), 0 }).x;
}

template<typename T>
int pixel_to_rcoord(T pixel) {
	return static_cast<int>(std::round(pixel_to_coord(pixel)));
}

void throw_error(std::string_view error);