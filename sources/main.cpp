#include <SFML/Graphics.hpp>
#include <string>

#include "Script.hpp"
#include "images.hpp"

sf::RenderWindow window;
sf::Event main_event;
std::string FONTS_PATH;

double main_time = 0;
std::mutex time_m;

size_t print_offset = 0;

__forceinline void start_program(char* cmd_line) {
    window.create(sf::VideoMode(1400, 800), "Moonshine - Lua loader", sf::Style::Default, sf::ContextSettings(0, 0, 16));
    
    sf::Clock clock;
    Script lua;

    if (cmd_line[0] != '\0')
        lua.open(cmd_line);

    sf::Image icon;
    icon.loadFromMemory(res_icon, sizeof(res_icon));

    window.setIcon(256, 256, icon.getPixelsPtr());

    sf::Texture background_texture;
    background_texture.loadFromMemory(res_background, sizeof(res_background));

    sf::Sprite background(background_texture);
    background.setScale(0.73, 0.74);

    sf::Font font;
    if (!font.loadFromFile(FONTS_PATH + "arial.ttf"))
        throw_error("Failed to create the font face.");

    sf::Text label_text("Script name:", font, 25);
    label_text.setPosition(sf::Vector2f(window.getSize().x / 2 - label_text.getGlobalBounds().width - 65, window.getSize().y / 2 - 15));

    sf::Text entered_text("", font, 25);
    std::string entered_tmp;

    sf::Text cursor("_", font, 25);
    bool cursor_visible = true;
    double cursor_timer = 0;

    while (window.isOpen()) {
        time_m.lock();
        main_time = static_cast<double>(clock.getElapsedTime().asMicroseconds()) / 800.f;
        time_m.unlock();

        clock.restart();

        if (!lua.is_open()) {
            entered_text.setString(entered_tmp);
            entered_text.setPosition(sf::Vector2f(label_text.getPosition().x + label_text.getGlobalBounds().width + 10, label_text.getPosition().y));
            
            cursor.setPosition(sf::Vector2f(entered_text.getPosition().x + entered_text.getGlobalBounds().width + 5, entered_text.getPosition().y));

            if (cursor_timer >= 600) {
                cursor_visible = !cursor_visible;
                cursor_timer = 0;
            }
            
            cursor_timer += main_time;

            window.clear();

            window.draw(background);
            window.draw(entered_text);
            window.draw(label_text);
            if (cursor_visible) window.draw(cursor);

            window.display();
        }

        closing_window_m.lock();

        while (window.pollEvent(main_event)) {
            if (main_event.type == sf::Event::Closed)
                window.close();

            if (main_event.type == sf::Event::MouseEntered) {
                cursor_in_window_m.lock();
                f_cursor_in_window = true;
                cursor_in_window_m.unlock();
            }

            if (main_event.type == sf::Event::MouseLeft) {
                cursor_in_window_m.lock();
                f_cursor_in_window = false;
                cursor_in_window_m.unlock();
            }

            if (lua.is_open()) continue;

            if (main_event.type == sf::Event::TextEntered) {
                if (main_event.key.code == 22)                           // 22 = Ctrl + V
                    entered_tmp += std::move(sf::Clipboard::getString());

                if (main_event.key.code == 8 && !entered_tmp.empty())    // 8 = Backspace
                    entered_tmp.pop_back();

                if (main_event.text.unicode > 31 && main_event.text.unicode < 128)
                    entered_tmp += static_cast<char>(main_event.text.unicode);
            }

            if (main_event.type == sf::Event::KeyPressed) {
                if (main_event.key.code == sf::Keyboard::Enter && !entered_tmp.empty())
                    lua.open(entered_tmp);
            }
        }

        closing_window_m.unlock();
    }
}

#ifdef _WIN32
#include <windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    FONTS_PATH = "C:/WINDOWS/Fonts/";

    start_program(lpCmdLine);
    return 0;
}
#elif defined(__linux__)
int main(int argc, char** argv) {
    FONTS_PATH = "/usr/share/fonts/";

    start_program(argv[0]);
    return 0;
}
#endif