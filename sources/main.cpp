#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "Script.hpp"

sf::RenderWindow window;
std::string FONTS_PATH;
size_t print_offset = 0;

std::map<std::string, std::pair<sf::Sprite, sf::Texture>> sprite_buffer;
std::map<std::string, std::pair<sf::Font, size_t>> font_buffer;

__forceinline void start_program(char* cmd_line) {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 16;

    window.create(sf::VideoMode(1400, 800), "Script Loader", sf::Style::Default, settings);
    window.setFramerateLimit(100);

    //std::string script_path = cmd_line[0] ? cmd_line : "";
    Script lua("C:/Users/tosha/OneDrive/Desktop/main.lua");

    sf::Event events;

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

    start_program(lpCmdLine);
    return 0;
}
#endif

#ifdef linux
int main(int argc, char** argv) {
    FONTS_PATH = "";

    start_program(argv[0]);
    return 0;
}
#endif