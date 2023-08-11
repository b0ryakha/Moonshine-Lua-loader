#pragma once

#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>

using ushort_t = unsigned short;

extern sf::RenderWindow window;
extern sf::Event main_event;
extern std::string font_path;

template<typename T>
__forceinline float pixel_to_coord(const T& point) {
	return window.mapPixelToCoords(sf::Vector2i(point, 0)).x;
}

void throw_error(std::string_view error) noexcept;