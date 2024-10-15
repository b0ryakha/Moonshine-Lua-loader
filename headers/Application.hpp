#pragma once
#include "Script.hpp"

#include <SFML/Graphics.hpp>

class Label;
class TextBox;

class Application final : public sf::RenderWindow {
private:
    Script lua;

    sf::Sprite* background = nullptr;
    Label* hint = nullptr;
    TextBox* textbox = nullptr;

    void render();
    void update();

protected:
    Application(int argc, char** argv);

public:
    ~Application();
	Application(Application& other) = delete;
    void operator=(const Application&) = delete;
    
    static inline sf::Vector2u init_size = { 1400, 800 };
    sf::Event event;

#ifdef _WIN32
    static inline std::string font_path = "C:/WINDOWS/Fonts/";
#elif defined(__linux__)
    static inline std::string font_path = "/usr/share/fonts/TTF/";
#endif

    static Application* instance(int argc = 0, char** argv = nullptr);
    int exec();
};