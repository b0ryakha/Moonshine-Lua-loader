#include "Script.hpp"

Script::Script() {}

Script::Script(const std::string& path) {
    open(path);
}

Script::~Script() {
    close();
}

void Script::close() {
    if (main_thread != nullptr) {
        delete main_thread;
        main_thread = nullptr;
    }

    if (lua_state != nullptr)
        lua_close(lua_state);

    window.setActive(true);
}

void Script::open(const std::string& path) {
    if (main_thread != nullptr) {
        throw_error("Script is already running.");
    }

    lua_state = luaL_newstate();

    if (lua_state == nullptr) {
        throw_error("Failed to create lua state.");
    }
    
    luaL_openlibs(lua_state);
    open_API();

    window.setActive(false);

    main_thread = new std::thread([&] {
        window.setActive(true);

        window.clear();
        window.display();

        if (luaL_dofile(lua_state, path.c_str()) != 0)
            throw_error(static_cast<std::string>(lua_tostring(lua_state, -1)) + ".");

        lua_pcall(lua_state, 0, 0, 0);

        window.setActive(false);
    });

    main_thread->join();
}

__forceinline void Script::open_API() {
    lua_register_table(lua_state, "render", {
        std::make_pair("text", lua::render_text),
        std::make_pair("measure_text", lua::render_measure_text),
        //std::make_pair("circle", lua::render_circle),
        //std::make_pair("outline_circle", lua::render_outline_circle),
        //std::make_pair("textured_circle", lua::render_textured_circle),
        //std::make_pair("rectangle", lua::render_rectangle),
        //std::make_pair("polygon", lua::render_polygon),
        //std::make_pair("convex", lua::render_convex),
        //std::make_pair("line", lua::render_line),
        //std::make_pair("ellipse", lua::render_ellipse),
        std::make_pair("sprite", lua::render_sprite),
        std::make_pair("new_sprite", lua::render_new_sprite),
        std::make_pair("load_font", lua::render_load_font),
    });

    lua_register_table(lua_state, "color", {
        std::make_pair("new", lua::color_new),
        std::make_pair("unpack", lua::color_unpack),
        std::make_pair("to_hex", lua::color_to_hex),
    });

    lua_register_table(lua_state, "window", {
        std::make_pair("get_size", lua::get_size),
        std::make_pair("display", lua::display),
        std::make_pair("clear", lua::clear),
        std::make_pair("close", lua::close),
        std::make_pair("sleep", lua::sleep),
        //std::make_pair("set_icon", lua::set_icon),
        //std::make_pair("set_title", lua::set_title),
    });

    std::vector<std::pair<std::string, LuaMultiValue>> SFML_KEYS;
    std::array<std::string, 101> SFML_KEYS_NAME { "A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z","Num0","Num1","Num2","Num3","Num4","Num5","Num6","Num7","Num8","Num9","Escape","LControl","LShift","LAlt","LSystem","RControl","RShift","RAlt","RSystem","Menu","LBracket","RBracket","Semicolon","Comma","Period","Quote","Slash","Backslash","Tilde","Equal","Hyphen","Space","Enter","Backspace","Tab","PageUp","PageDown","End","Home","Insert","Delete","Add","Subtract","Multiply","Divide","Left","Right","Up","Down","Numpad0","Numpad1","Numpad2","Numpad3","Numpad4","Numpad5","Numpad6","Numpad7","Numpad8","Numpad9","F1","F2","F3","F4","F5","F6","F7","F8","F9","F10","F11","F12","F13","F14","F15","Pause" };

    for (size_t i = 0; i < SFML_KEYS_NAME.size(); ++i) {
        SFML_KEYS.push_back(std::make_pair(SFML_KEYS_NAME[i], i));
    }

    SFML_KEYS.push_back(std::make_pair("Dash", 56));
    SFML_KEYS.push_back(std::make_pair("BackSpace", 59));
    SFML_KEYS.push_back(std::make_pair("BackSlash", 53));
    SFML_KEYS.push_back(std::make_pair("Semicolon", 48));
    SFML_KEYS.push_back(std::make_pair("Return", 58));

    lua_register_table(lua_state, "key", SFML_KEYS);

    lua_register_table(lua_state, "keyboard", {
        //std::make_pair("get_ch", lua::get_ch),
        //std::make_pair("is_pressed", lua::is_key_pressed),
    });

    std::vector<std::pair<std::string, LuaMultiValue>> SFML_BUTTONS;
    std::array<std::string, 5> SFML_BUTTONS_NAME { "Left", "Right", "Middle", "XButton1", "XButton2" };

    for (size_t i = 0; i < SFML_BUTTONS_NAME.size(); ++i) {
        SFML_BUTTONS.push_back(std::make_pair(SFML_BUTTONS_NAME[i], i));
    }

    lua_register_table(lua_state, "button", SFML_BUTTONS);

    lua_register_table(lua_state, "mouse", {
        //std::make_pair("is_pressed", lua::is_button_pressed),
        ////std::make_pair("is_scrolling_up", lua::is_scrolling_up),
        ////std::make_pair("is_scrolling_down", lua::is_scrolling_down),
    });

    lua_register_table(lua_state, "cursor", {
        //std::make_pair("get_x", lua::cursor_get_x),
        //std::make_pair("get_y", lua::cursor_get_y),
        //std::make_pair("set_pos", lua::cursor_set_pos),
        //std::make_pair("in_bounds", lua::cursor_in_bounds),
    });

    lua_register_table(lua_state, "view", {
        //std::make_pair("set", lua::view_set),
        //std::make_pair("set_ported", lua::view_set_ported),
        //std::make_pair("get_x", lua::view_get_x),
        //std::make_pair("get_y", lua::view_get_y),
    });

    lua_register_table(lua_state, "sound", {
        //std::make_pair("play", lua::sound_play),
        ////std::make_pair("set_active", ),
    });

    lua_register_table(lua_state, "file", {
        //std::make_pair("exists", lua::file_exists),
        //std::make_pair("create", lua::file_create),
        //std::make_pair("remove", lua::file_remove),
        //std::make_pair("push", lua::file_push),
        //std::make_pair("pop", lua::file_pop),
        ////std::make_pair("get_line", ),
        ////std::make_pair("set_line", ),
        ////std::make_pair("get", ),
        ////std::make_pair("set", ),
        ////std::make_pair("line_count", ),
        ////std::make_pair("clear", ),
        ////std::make_pair("rename", ),
    });

    lua_register_table(lua_state, "cmath", {
        std::make_pair("rand", lua::rand_int),
        std::make_pair("lerp", lua::lerp),
        std::make_pair("clamp", lua::clamp),
    });

    lua_register_table(lua_state, "globalvars", {
        //std::make_pair("get_frametime", lua::get_frametime),
    });

    lua_register(lua_state, "print", lua::print);
}