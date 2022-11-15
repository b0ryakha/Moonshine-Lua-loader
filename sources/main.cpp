#include "Script.h"
#include <SFML/Graphics.hpp>

sf::RenderWindow window;

__forceinline void start_program() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 16;

    window.create(sf::VideoMode(1400, 800), "Script Loader", sf::Style::Default, settings);
    window.setFramerateLimit(100);

    sf::Event events;

    Script lua("C:/Users/tosha/OneDrive/Desktop/test1.lua");

    while (window.isOpen()) {
        while (window.pollEvent(events)) {
            if (events.type == sf::Event::Closed)
                window.close();
        }
    }
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