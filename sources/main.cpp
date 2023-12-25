#include <SFML/Graphics.hpp>
#include <string>

#include "Script.hpp"
#include "images.hpp"

#include "Label.hpp"
#include "TextBox.hpp"

sf::RenderWindow window;
sf::Event main_event;
std::string font_path;

void start_program(std::string_view cmd_line) {
    window.create(sf::VideoMode(1400u, 800u), "Moonshine - Lua loader", sf::Style::Default, sf::ContextSettings(0u, 0u, 16u));

    Script lua;
    if (!cmd_line.empty())
        lua.open(cmd_line);

    sf::Image icon;
    icon.loadFromMemory(res_icon, sizeof(res_icon));

    window.setIcon(256, 256, icon.getPixelsPtr());

    sf::Texture background_texture;
    background_texture.loadFromMemory(res_background, sizeof(res_background));

    sf::Sprite background(background_texture);
    background.setScale(0.74f, 0.74f);

    Label hint("Enter the path to the lua script ...", font_path + "arial.ttf", 25);
    hint.setPosition(sf::Vector2f(window.getSize().x / 2 - hint.getGlobalBounds().width / 2, window.getSize().y / 2 + 300));
    hint.setFillColor(sf::Color(55, 55, 55, 200));

    TextBox textbox(font_path + "arial.ttf", window.getSize().x / 2 - 205, window.getSize().y / 2 - 21, 410, 42, false);
    textbox.setBlinkerColor(sf::Color::White);
    textbox.setTextColor(sf::Color::White);
    textbox.focus();

    while (window.isOpen()) {
        if (!lua.is_open()) {
            window.clear();
            window.draw(background);
            window.draw(hint);
            textbox.draw(window);
            window.display();
        }

        if (window.pollEvent(main_event)) {
            if (!lua.is_open()) {
                textbox.handleEvent(main_event);

                if (textbox.isEntered())
                    lua.open(textbox.getText());
            }

            if (main_event.type == sf::Event::Closed)
                window.close();

            if (main_event.type == sf::Event::MouseEntered) {
                cursor_in_window_m.lock();
                is_cursor_in_window = true;
                cursor_in_window_m.unlock();
            }

            if (main_event.type == sf::Event::MouseLeft) {
                cursor_in_window_m.lock();
                is_cursor_in_window = false;
                cursor_in_window_m.unlock();
            }
        }
    }
}

#ifdef _WIN32
#include <windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    font_path = "C:/WINDOWS/Fonts/";
    start_program(lpCmdLine);
}

#elif defined(__linux__)
int main(int argc, char** argv) {
    font_path = "/usr/share/fonts/TTF/";
    start_program(argc > 1 ? argv[1] : "");
}
#endif