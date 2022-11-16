#include <SFML/Graphics.hpp>
#include <string>

#include "Script.h"

sf::RenderWindow window;
std::string FONTS_PATH;

__forceinline void start_program() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 16;

    window.create(sf::VideoMode(1400, 800), "Script Loader", sf::Style::Default, settings);
    window.setFramerateLimit(100);

    sf::Event events;

    Script lua("C:/Users/tosha/OneDrive/Desktop/main.lua");

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
    FONTS_PATH = "C:/WINDOWS/Fonts/";

    start_program();
    return 0;
}
#endif

#ifdef linux
int main() {
    FONTS_PATH = "";

    start_program();
    return 0;
}
#endif