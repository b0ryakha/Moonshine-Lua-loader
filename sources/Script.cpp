#include "Script.hpp"

Script::Script(const std::string& path) {
    open(path);
}

Script::~Script() {
    close();
}

void Script::close() const {
    if (is_open()) {
        delete main_thread;
        main_thread = nullptr;
    }

    if (lua_state != nullptr)
        lua_close(lua_state);

    window.setActive(true);
}

void Script::open(const std::string& path) const {
    if (is_open())
        return;

    lua_state = luaL_newstate();

    if (lua_state == nullptr)
        throw_error("Failed to create lua state.");

    lua_path = std::move(const_cast<std::string&>(path));

    if (!lua_path.empty() && lua_path[0] == '\"' && lua_path[lua_path.length() - 1] == '\"')
        lua_path = std::string(lua_path.begin() + 1, lua_path.end() - 1);
    
    if (lua_path.find('/') == std::string::npos && lua_path.find('\\') == std::string::npos)
        lua_path = "./" + lua_path;

    luaL_openlibs(lua_state);
    open_API();

    window.clear();
    window.setActive(false);

    main_thread = new std::thread([&] {
        if (luaL_dofile(lua_state, lua_path.c_str()) != 0)
            throw_error(std::string(lua_tostring(lua_state, -1)) + ".");

        lua_pcall(lua_state, 0, 0, 0);
    });

    main_thread->detach();
}

__forceinline void Script::open_API() const {
    lua_register_table(lua_state, "render", {
        std::make_pair("text", API::render_text),
        std::make_pair("sprite", API::render_sprite),
        std::make_pair("measure_text", API::render_measure_text),
        std::make_pair("rectangle", API::render_rectangle),
        std::make_pair("circle", API::render_circle),
        std::make_pair("line", API::render_line),
        std::make_pair("polygon", API::render_polygon),
        //std::make_pair("blur", API::render_blur),
        //std::make_pair("shadow", API::render_shadow),
    });

    lua_register_table(lua_state, "window", {
        std::make_pair("get_size", API::window_get_size),
        std::make_pair("set_size", API::window_set_size),
        std::make_pair("display", API::window_display),
        std::make_pair("clear", API::window_clear),
        std::make_pair("close", API::window_close),
        std::make_pair("capture", API::window_capture),
        std::make_pair("sleep", API::window_sleep),
        std::make_pair("await", API::window_await),
        std::make_pair("get_pos", API::window_get_pos),
        std::make_pair("set_pos", API::window_set_pos),
        std::make_pair("set_title", API::window_set_title),
        std::make_pair("set_vsync", API::window_set_vsync),
        std::make_pair("set_frame_limit", API::window_set_frame_limit),
        std::make_pair("set_icon", API::window_set_icon)
    });

    std::vector<std::pair<std::string, LuaMultiValue_t>> SFML_KEYS;
    constexpr std::array<std::string_view, 101> SFML_KEYS_NAME = { "A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z","Num0","Num1","Num2","Num3","Num4","Num5","Num6","Num7","Num8","Num9","Escape","LControl","LShift","LAlt","LSystem","RControl","RShift","RAlt","RSystem","Menu","LBracket","RBracket","Semicolon","Comma","Period","Quote","Slash","Backslash","Tilde","Equal","Hyphen","Space","Enter","Backspace","Tab","PageUp","PageDown","End","Home","Insert","Delete","Add","Subtract","Multiply","Divide","Left","Right","Up","Down","Numpad0","Numpad1","Numpad2","Numpad3","Numpad4","Numpad5","Numpad6","Numpad7","Numpad8","Numpad9","F1","F2","F3","F4","F5","F6","F7","F8","F9","F10","F11","F12","F13","F14","F15","Pause" };

    for (size_t i = 0, size = SFML_KEYS_NAME.size(); i < size; ++i)
        SFML_KEYS.emplace_back(std::make_pair(SFML_KEYS_NAME[i], i));

    SFML_KEYS.emplace_back(std::make_pair("Dash", 56));
    SFML_KEYS.emplace_back(std::make_pair("BackSpace", 59));
    SFML_KEYS.emplace_back(std::make_pair("BackSlash", 53));
    SFML_KEYS.emplace_back(std::make_pair("Semicolon", 48));
    SFML_KEYS.emplace_back(std::make_pair("Return", 58));

    lua_register_table(lua_state, "key", SFML_KEYS);

    lua_register_table(lua_state, "keyboard", {
        std::make_pair("get_pressed", API::keyboard_get_pressed),
        std::make_pair("is_pressed", API::keyboard_is_pressed),
    });

    std::vector<std::pair<std::string, LuaMultiValue_t>> SFML_BUTTONS;
    constexpr std::array<std::string_view, 5> SFML_BUTTONS_NAME = { "Left", "Right", "Middle", "XButton1", "XButton2" };

    for (size_t i = 0, size = SFML_BUTTONS_NAME.size(); i < size; ++i)
        SFML_BUTTONS.emplace_back(std::make_pair(SFML_BUTTONS_NAME[i], i));

    lua_register_table(lua_state, "button", SFML_BUTTONS);

    lua_register_table(lua_state, "mouse", {
        std::make_pair("get_pressed", API::mouse_get_pressed),
        std::make_pair("is_pressed", API::mouse_is_pressed),
        std::make_pair("is_scrolling_up", API::mouse_is_scrolling_up),
        std::make_pair("is_scrolling_down", API::mouse_is_scrolling_down),
    });

    lua_register_table(lua_state, "cursor", {
        std::make_pair("get_pos", API::cursor_get_pos),
        std::make_pair("set_pos", API::cursor_set_pos),
        std::make_pair("in_bounds", API::cursor_in_bounds),
        std::make_pair("in_window", API::cursor_in_window),
    });

    lua_register_table(lua_state, "file", {
        std::make_pair("read", API::file_read),
        std::make_pair("write", API::file_write),
        std::make_pair("download", API::file_download),
        std::make_pair("create", API::file_create),
        std::make_pair("remove", API::file_remove),
        std::make_pair("exists", API::file_exists),
        std::make_pair("line_count", API::file_line_count),
        std::make_pair("clear", API::file_clear),
        std::make_pair("rename", API::file_rename),
        std::make_pair("get_list", API::file_get_list),
    });

    lua_register_table(lua_state, "cmath", {
        std::make_pair("rand_int", API::rand_int),
        std::make_pair("rand_double", API::rand_double),
        std::make_pair("lerp", API::lerp),
        std::make_pair("clamp", API::clamp),
    });

    lua_register_table(lua_state, "globalvars", {
        std::make_pair("get_frametime", API::get_frametime),
        std::make_pair("get_executable_path", API::get_executable_path),
    });

    lua_register(lua_state, "print", API::print);

    lua_register_class<API::Font>(lua_state, "Font");
    lua_register_class<API::Vector2>(lua_state, "Vector2");
    lua_register_class<API::Color>(lua_state, "Color");
    lua_register_class<API::Sound>(lua_state, "Sound");
    lua_register_class<API::Sprite>(lua_state, "Sprite");
    lua_register_class<API::View>(lua_state, "View");
}

bool Script::is_open() const {
    return main_thread != nullptr;
}