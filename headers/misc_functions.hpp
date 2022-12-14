#pragma once

#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include <string>
#include <iterator>
#include <mutex>

extern sf::RenderWindow window;
extern sf::Event main_event;
extern std::string FONTS_PATH;

inline std::mutex closing_window_m;

void throw_error(const std::string& error) noexcept;
std::string number_to_str(double n);