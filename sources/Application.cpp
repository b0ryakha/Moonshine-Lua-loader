#include "Application.hpp"
#include "images.hpp"
#include "Label.hpp"
#include "TextBox.hpp"

#include "API/cursor.hpp"
#include "API/globalvars.hpp"

Application::Application(int argc, char** argv)
    : sf::RenderWindow(sf::VideoMode(init_size.x, init_size.y), "Moonshine - Lua loader", sf::Style::Default, sf::ContextSettings(0, 0, 16))
{
    RenderWindow::setVerticalSyncEnabled(true);

    sf::Image icon;
    icon.loadFromMemory(res_icon, sizeof(res_icon));
    RenderWindow::setIcon(256, 256, icon.getPixelsPtr());

    if (argc > 2) {
        args.reserve(argc - 2);
        for (int i = 2; i < argc; ++i)
            args.emplace_back(std::string(argv[i]));
    }

    if (argc > 1) {
        RenderWindow::setActive(false);
        lua.open(argv[1]);
        return;
    }

    const auto arial = font_path + "Arial.TTF";

    static sf::Texture bg_texture;
    bg_texture.loadFromMemory(res_background, sizeof(res_background));
    background = new sf::Sprite(bg_texture);
    background->setScale(0.74f, 0.74f);

    hint = new Label("Enter the path to the lua script ...", arial, 25);
    hint->setPosition(sf::Vector2f(init_size.x / 2.f - hint->getGlobalBounds().width / 2.f, init_size.y / 2.f + 300));
    hint->setFillColor(sf::Color(55, 55, 55, 200));

    textbox = new TextBox(arial, init_size.x / 2.f - 205.f, init_size.y / 2.f - 21.f, 410, 42, false);
    textbox->setBlinkerColor(sf::Color::White);
    textbox->setTextColor(sf::Color::White);
    textbox->focus();
}

Application::~Application() {
    delete background;
    delete hint;
    delete textbox;
}

int Application::exec() {
    while (isOpen()) {
        update();
        render();
    }

    return 0;
}

void Application::render() {
    if (lua.is_open()) return;

    RenderWindow::clear();
    RenderWindow::draw(*background);
    RenderWindow::draw(*hint);
    textbox->draw(*this);
    RenderWindow::display();
}

void Application::update() {
    if (!RenderWindow::pollEvent(event)) return;

    if (!lua.is_open()) {
        textbox->handleEvent(event);

        if (textbox->isEntered()) {
            RenderWindow::clear();
            RenderWindow::display();
            RenderWindow::setActive(false);
            lua.open(textbox->getText());
        }
    }

    if (event.type == sf::Event::Closed) {
        RenderWindow::close();
        std::exit(0);
    }

    if (event.type == sf::Event::MouseEntered) {
        std::lock_guard<std::mutex> lock(cursor_in_window_m);
        is_cursor_in_window = true;
    }

    if (event.type == sf::Event::MouseLeft) {
        std::lock_guard<std::mutex> lock(cursor_in_window_m);
        is_cursor_in_window = false;
    }
}

Application* Application::instance(int argc, char** argv) {
    static auto instance = Application(argc, argv);
    return &instance;
}