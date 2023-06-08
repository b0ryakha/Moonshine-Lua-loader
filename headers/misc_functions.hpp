#pragma once

#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>

using ushort_t = unsigned short;

extern sf::RenderWindow window;
extern sf::Event main_event;
extern std::string font_path;

void throw_error(std::string_view error) noexcept;