#include "Application.hpp"
#include "images.hpp"
#include "Label.hpp"
#include "TextBox.hpp"

#include "API/cursor.hpp"
#include "API/globalvars.hpp"

Application::Application(int argc, char** argv)
    : sf::RenderWindow(sf::VideoMode(init_size), "Moonshine - Lua loader", sf::State::Windowed, settings)
{
    RenderWindow::setVerticalSyncEnabled(true);

    sf::Image icon;
    icon.loadFromMemory(res_icon, sizeof(res_icon));
    RenderWindow::setIcon(sf::Image(sf::Vector2u(256, 256), icon.getPixelsPtr()));

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
    background->setScale(sf::Vector2f(0.74f, 0.74f));

    hint = new Label("Enter the path to the lua script ...", arial, 25);
    hint->setPosition(sf::Vector2f(init_size.x / 2.f - hint->getGlobalBounds().size.x / 2.f, init_size.y / 2.f + 300));
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
    while (const auto event = pollEvent()) {
        if (!lua.is_open()) {
            textbox->handleEvent(*event);

            if (textbox->isEntered()) {
                RenderWindow::clear();
                RenderWindow::display();
                RenderWindow::setActive(false);
                lua.open(textbox->getText());
            }
        }

        if (event->is<sf::Event::Closed>()) {
            RenderWindow::close();
            std::exit(0);
        }

        if (new_state != -1) {
            RenderWindow::create(new_mode, title, sf::State(new_state), settings);
            RenderWindow::setActive(false); // because window is using in another thread and it is active there.

            std::lock_guard<std::mutex> lock(style_lock);
            new_state = -1;
        }

        if (event->is<sf::Event::MouseEntered>()) {
            std::lock_guard<std::mutex> lock(cursor_in_window_m);
            is_cursor_in_window = true;
        }

        if (event->is<sf::Event::MouseLeft>()) {
            std::lock_guard<std::mutex> lock(cursor_in_window_m);
            is_cursor_in_window = false;
        }
    }
}

Application* Application::instance(int argc, char** argv) {
    static auto instance = Application(argc, argv);
    return &instance;
}

void Application::setTitle(const sf::String& title) {
    this->title = std::move(title);
    RenderWindow::setTitle(this->title);
}

void Application::setSize(const sf::Vector2u& size) {
    old_size = size;
    RenderWindow::setSize(old_size);
}

sf::Vector2u Application::getOldSize() const {
    return old_size;
}

sf::Vector2u Application::getInitSize() const {
    return init_size;
}

void Application::setState(const sf::VideoMode& mode, sf::State state) {
    style_lock.lock();
    new_mode = mode;
    new_state = (int)state;
    style_lock.unlock();

    RenderWindow::setActive(false);

    while (new_state != -1) //wait main thread
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
}