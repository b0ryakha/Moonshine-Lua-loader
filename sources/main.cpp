#include "Script.h"
#include <SFML/Graphics.hpp>

__forceinline void start_program() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 16;

    sf::RenderWindow window(sf::VideoMode(1400, 800), "Script Loader", sf::Style::Default, settings);
    window.setFramerateLimit(100);

    Script lua(window, "C:/Users/tosha/OneDrive/Desktop/test.lua");

    while (window.isOpen()) {};
}

#ifdef _WIN32
#include <windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    start_program();
    return 0;
}
#endif

#ifdef linux
int main() {
    start_program();
    return 0;
}
#endif