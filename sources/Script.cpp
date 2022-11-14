#include "Script.h"

Script::Script(sf::RenderWindow& window, const std::string& path) {
    lua_state = luaL_newstate();

    if (lua_state == 0) {
        // Failed to create Lua state
        return;
    }

    luaL_openlibs(lua_state);
    open_API();

    window.setActive(false);

    main_thread = new std::thread([&] {
        window.setActive(true);

        if (luaL_dofile(lua_state, path.c_str()) != 0) {
            // Failed to load script
        }
        else {
            lua_pcall(lua_state, 0, 0, 0);
        }

        window.setActive(false);
    });

    main_thread->detach();
}

Script::~Script() {
	delete main_thread;
	main_thread = nullptr;

    lua_close(lua_state);
}

__forceinline void Script::open_API() {
    lua_register_table(lua_state, "render", {
        //std::make_pair("text", lua_render_text),
        //std::make_pair("measure_text", lua_render_measure_text),
        //std::make_pair("circle", lua_render_circle),
        //std::make_pair("outline_circle", lua_render_outline_circle),
        //std::make_pair("textured_circle", lua_render_textured_circle),
        //std::make_pair("rectangle", lua_render_rectangle),
        //std::make_pair("polygon", lua_render_polygon),
        //std::make_pair("convex", lua_render_convex),
        //std::make_pair("line", lua_render_line),
        //std::make_pair("ellipse", lua_render_ellipse),
        //std::make_pair("image", lua_render_image),
        //std::make_pair("image_ex", lua_render_image_ex),
        //std::make_pair("sprite", lua_render_sprite),
        //std::make_pair("sprite_ex", lua_render_sprite_ex),
    });

    lua_register_table(lua_state, "color", {
        //std::make_pair("new", lua_color_new),
    });

    lua_register_table(lua_state, "window", {
        //std::make_pair("get_width", lua_get_screen_width),
        //std::make_pair("get_height", lua_get_screen_height),
        //std::make_pair("refresh", lua_screen_refresh),
        //std::make_pair("clear", lua_clear_screen),
        //std::make_pair("close", lua_close_screen),
        //std::make_pair("sleep", lua_wait),
        //std::make_pair("set_icon", lua_set_icon),
        //std::make_pair("set_title", lua_set_title),
    });

    std::vector<std::pair<std::string, std::variant<lua_Number, lua_CFunction, std::string>>> SFML_KEYS;
    std::array<std::string, 101> SFML_KEYS_NAME { "A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z","Num0","Num1","Num2","Num3","Num4","Num5","Num6","Num7","Num8","Num9","Escape","LControl","LShift","LAlt","LSystem","RControl","RShift","RAlt","RSystem","Menu","LBracket","RBracket","Semicolon","Comma","Period","Quote","Slash","Backslash","Tilde","Equal","Hyphen","Space","Enter","Backspace","Tab","PageUp","PageDown","End","Home","Insert","Delete","Add","Subtract","Multiply","Divide","Left","Right","Up","Down","Numpad0","Numpad1","Numpad2","Numpad3","Numpad4","Numpad5","Numpad6","Numpad7","Numpad8","Numpad9","F1","F2","F3","F4","F5","F6","F7","F8","F9","F10","F11","F12","F13","F14","F15","Pause" };

    for (int i = 0; i < SFML_KEYS_NAME.size(); ++i) {
        SFML_KEYS.push_back(std::make_pair(SFML_KEYS_NAME[i], i));
    }

    SFML_KEYS.push_back(std::make_pair("Dash", 56));
    SFML_KEYS.push_back(std::make_pair("BackSpace", 59));
    SFML_KEYS.push_back(std::make_pair("BackSlash", 53));
    SFML_KEYS.push_back(std::make_pair("Semicolon", 48));
    SFML_KEYS.push_back(std::make_pair("Return", 58));

    lua_register_table(lua_state, "key", SFML_KEYS);

    lua_register_table(lua_state, "keyboard", {
        //std::make_pair("get_ch", lua_get_ch),
        //std::make_pair("is_pressed", lua_is_key_pressed),
    });

    std::vector<std::pair<std::string, std::variant<lua_Number, lua_CFunction, std::string>>> SFML_BUTTONS;
    std::array<std::string, 5> SFML_BUTTONS_NAME { "Left", "Right", "Middle", "XButton1", "XButton2" };

    for (int i = 0; i < SFML_BUTTONS_NAME.size(); ++i) {
        SFML_BUTTONS.push_back(std::make_pair(SFML_BUTTONS_NAME[i], i));
    }

    lua_register_table(lua_state, "button", SFML_BUTTONS);

    lua_register_table(lua_state, "mouse", {
        //std::make_pair("is_pressed", lua_is_button_pressed),
        ////std::make_pair("is_scrolling_up", lua_is_scrolling_up),
        ////std::make_pair("is_scrolling_down", lua_is_scrolling_down),
    });

    lua_register_table(lua_state, "cursor", {
        //std::make_pair("get_x", lua_cursor_get_x),
        //std::make_pair("get_y", lua_cursor_get_y),
        //std::make_pair("set_pos", lua_cursor_set_pos),
        //std::make_pair("in_bounds", lua_cursor_in_bounds),
    });

    lua_register_table(lua_state, "view", {
        //std::make_pair("set", lua_view_set),
        //std::make_pair("set_ported", lua_view_set_ported),
        //std::make_pair("get_x", lua_view_get_x),
        //std::make_pair("get_y", lua_view_get_y),
    });

    lua_register_table(lua_state, "sound", {
        //std::make_pair("play", lua_sound_play),
        ////std::make_pair("set_active", ),
    });

    lua_register_table(lua_state, "file", {
        //std::make_pair("exists", lua_file_exists),
        //std::make_pair("create", lua_file_create),
        //std::make_pair("remove", lua_file_remove),
        //std::make_pair("push", lua_file_push),
        //std::make_pair("pop", lua_file_pop),
        ////std::make_pair("get_line", ),
        ////std::make_pair("set_line", ),
        ////std::make_pair("get", ),
        ////std::make_pair("set", ),
        ////std::make_pair("line_count", ),
        ////std::make_pair("clear", ),
        ////std::make_pair("rename", ),
    });

    lua_register_table(lua_state, "cmath", {
        //std::make_pair("rand", lua_rand_number),
        //std::make_pair("lerp", lua_lerp),
    });

    lua_register_table(lua_state, "globalvars", {
        //std::make_pair("get_frametime", lua_get_frametime),
    });

    //lua_register(lua_state, "print", lua_print);
}