#pragma once
#include "Script.hpp"

#include <SFML/Graphics.hpp>

class Label;
class TextBox;

class Application final : public sf::RenderWindow {
private:
    Script lua;
    bool is_main_menu = true;
    bool need_reload = false;
    bool need_close = false;

    sf::String title;
    static inline sf::Vector2u init_size = { 1400, 800 };
    static inline sf::ContextSettings settings = sf::ContextSettings(0, 0, 16);
    sf::Vector2u old_size = init_size;

    sf::Uint32 new_style = sf::Style::None;
    sf::VideoMode new_mode;
    std::mutex style_lock;

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
    
    sf::Event event;

#ifdef _WIN32
    static inline std::string font_path = "C:/WINDOWS/Fonts/";
#elif defined(__linux__)
    static inline std::string font_path = "/usr/share/fonts/TTF/";
#endif

    static Application* instance(int argc = 0, char** argv = nullptr);
    int exec();
    void setNeedReload();
    void setNeedClose();

    void setTitle(const sf::String& title);
    sf::Vector2u getOldSize() const;
    sf::Vector2u getInitSize() const;
    void setSize(const sf::Vector2u& size);
    void setStyle(const sf::VideoMode& mode, sf::Uint32 style);
};