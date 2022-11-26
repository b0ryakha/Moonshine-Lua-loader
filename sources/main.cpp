#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <array>
#include <mutex>

#include "Script.hpp"

sf::RenderWindow window;
sf::Event main_event;

double main_time = 0;
std::mutex time_m;

std::string FONTS_PATH;
size_t print_offset = 0;

std::map<std::string, std::pair<sf::Sprite, sf::Texture>> sprite_buffer;
std::map<std::string, std::pair<sf::Font, size_t>> font_buffer;

__forceinline void start_program(char* cmd_line) {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 16;

    sf::Clock clock;

    window.create(sf::VideoMode(1400, 800), "Script Loader", sf::Style::Default, settings);
    window.setFramerateLimit(100);
    
    Script lua;
    bool script_loaded = false;

    if (cmd_line[0] != '\0') {
        script_loaded = true;
        lua.open(cmd_line);
    }

    sf::Font font;
    if (!font.loadFromFile(FONTS_PATH + "arial.ttf"))
        throw_error("Failed to create the font face.");

    sf::Text label_text("Script name:", font, 20);
    label_text.setPosition(sf::Vector2f(window.getSize().x / 2 - label_text.getGlobalBounds().width, window.getSize().y / 2));

    sf::Text entered_text("", font, 20);
    std::string entered_tmp;

    while (window.isOpen()) {
        time_m.lock();
        main_time = static_cast<double>(clock.getElapsedTime().asMicroseconds()) / 800;
        time_m.unlock();

        clock.restart();

        if (!script_loaded) {
            window.clear();
            entered_text.setString(entered_tmp);
            entered_text.setPosition(sf::Vector2f(label_text.getPosition().x + label_text.getGlobalBounds().width + 10, label_text.getPosition().y));
            window.draw(entered_text);
            window.draw(label_text);
            window.display();
        }

        while (window.pollEvent(main_event)) {
            if (main_event.type == sf::Event::Closed)
                window.close();

            if (script_loaded) continue;

            if (main_event.type == sf::Event::TextEntered) {
                if (main_event.key.code == 22)                           // 22 = Ctrl + V
                    entered_tmp += std::move(sf::Clipboard::getString());

                if (main_event.key.code == 8 && !entered_tmp.empty())    // 8 = Backspace
                    entered_tmp.pop_back();

                if (main_event.text.unicode > 31 && main_event.text.unicode < 128)
                    entered_tmp += static_cast<char>(main_event.text.unicode);
            }

            if (main_event.type == sf::Event::KeyPressed) {
                if (main_event.key.code == sf::Keyboard::Enter && !entered_tmp.empty()) {
                    script_loaded = true;
                    lua.open(entered_tmp);
                }
            }
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