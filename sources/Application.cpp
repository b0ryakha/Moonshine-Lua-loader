#include "Application.hpp"
#include "images.hpp"
#include "Label.hpp"
#include "TextBox.hpp"

#include "API/cursor.hpp"
#include "API/globalvars.hpp"

Application::Application(int argc, char** argv)
    : sf::RenderWindow(sf::VideoMode(init_size.x, init_size.y), "Moonshine - Lua loader", sf::Style::Default, settings)
{
    RenderWindow::setVerticalSyncEnabled(true);

    sf::Image icon;
    icon.loadFromMemory(res_icon, sizeof(res_icon));
    RenderWindow::setIcon(256, 256, icon.getPixelsPtr());

    if (argc > 1) {
        args.reserve(argc - 1);

        std::string script = argv[1];
        
        auto index = script.find_last_of("/\\");
        if (index != std::string::npos)
            script = std::move(script.substr(index + 1));

        args.emplace_back(script);

        for (int i = 2; i < argc; ++i)
            args.emplace_back(std::string(argv[i]));

        RenderWindow::setActive(false);
        is_main_menu = false;
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
    while (sf::RenderWindow::isOpen()) {
        update();
        render();
    }

    return 0;
}

void Application::setNeedReload() {
    // make sure that script will be closed from API
    RenderWindow::setActive(false);
    need_reload = true;
    IS_SCRIPT_CLOSE = true;
}

void Application::setNeedClose() {
    // make sure that script will be closed from API
    RenderWindow::setActive(false);
    need_close = true;
    IS_SCRIPT_CLOSE = true;
}

void Application::render() {
    if (!is_main_menu || lua.is_open()) return;

    RenderWindow::clear();
    RenderWindow::draw(*background);
    RenderWindow::draw(*hint);
    textbox->draw(*this);
    RenderWindow::display();
}

void Application::update() {
    if (!RenderWindow::pollEvent(event)) return;

    if (is_main_menu && !lua.is_open()) {
        textbox->handleEvent(event);

        if (textbox->isEntered()) {
            RenderWindow::clear();
            RenderWindow::display();
            RenderWindow::setActive(false);
            lua.open(textbox->getText());
            is_main_menu = false;
        }
    }

    if (need_reload && lua.reload()) {
        need_reload = false;
    }

    if (need_close || event.type == sf::Event::Closed) {
        RenderWindow::close();
        std::exit(0);
    }

    if (new_style != sf::Style::None) {
        RenderWindow::create(new_mode, title, new_style, settings);
        RenderWindow::setActive(false); // because window is using in another thread and it is active there.

        std::lock_guard<std::mutex> lock(style_lock);
        new_style = sf::Style::None;
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

void Application::setStyle(const sf::VideoMode& mode, sf::Uint32 style) {
    style_lock.lock();
    new_mode = mode;
    new_style = style;
    style_lock.unlock();

    RenderWindow::setActive(false);

    while (new_style != sf::Style::None) //wait main thread
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
}