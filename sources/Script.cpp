#include "Script.hpp"

#include "API/Objects/Vector2.hpp"
#include "API/Objects/Color.hpp"
#include "API/Objects/Font.hpp"
#include "API/Objects/Sound.hpp"
#include "API/Objects/Sprite.hpp"
#include "API/Objects/View.hpp"

#include "API/cmath.hpp"
#include "API/cursor.hpp"
#include "API/file.hpp"
#include "API/globalvars.hpp"
#include "API/keyboard.hpp"
#include "API/mouse.hpp"
#include "API/render.hpp"
#include "API/window.hpp"
#include "API/network.hpp"
#include "API/hotreload.hpp"

#include "error_handler.hpp"

#include <array>

Script::Script(std::string_view path) {
    open(path);
}

bool Script::open(std::string_view path) {
    if (is_open()) return false;

    #ifndef _DEBUG
        freopen("/dev/null", "w", stderr);
    #endif

    lua_state = luaL_newstate();
    if (!lua_state) return false;

    lua_path = std::move(path);

    if (lua_path.size() >= 2 && lua_path.front() == '\"' && lua_path.back() == '\"')
        lua_path = lua_path.substr(1, lua_path.size() - 2);

    if (lua_path.find_first_of("/\\") == std::string::npos)
        lua_path = "./" + lua_path;

    luaL_openlibs(lua_state);
    resolve_path();
    open_API();

    future = std::async(std::launch::async, [&] {
        if (luaL_dofile(lua_state, lua_path.c_str()) != 0)
            throw_error(lua_tostring(lua_state, -1));

        if (lua_isfunction(lua_state, -1))
            lua_pcall(lua_state, 0, 0, 0);
    });

    return true;
}

bool Script::is_open() const {
    return lua_state && future.wait_for(std::chrono::milliseconds(1)) != std::future_status::ready;
}

bool Script::reload() {
    return open(lua_path);
}

void Script::resolve_path() {
    lua_getglobal(lua_state, "package");

    lua_getfield(lua_state, -1, "path");
    std::string path = lua_tostring(lua_state, -1);
    lua_pop(lua_state, 1);

    for (const auto& dir : { "./build", "./scripts", "./src", "./sources", "./source" })
        path += std::move(path + ";" + dir + "/?.lua");

    lua_pushstring(lua_state, path.c_str());
    lua_setfield(lua_state, -2, "path");
    lua_pop(lua_state, 1);
}

void Script::open_API() {
    lhelper::register_table(lua_state, "render", {
        std::make_pair("text", API::render_text),
        std::make_pair("sprite", API::render_sprite),
        std::make_pair("measure_text", API::render_measure_text),
        std::make_pair("outline_rectangle", API::render_outline_rectangle),
        std::make_pair("gradient", API::render_gradient),
        std::make_pair("rectangle", API::render_rectangle),
        std::make_pair("circle", API::render_circle),
        std::make_pair("line", API::render_line),
        std::make_pair("polygon", API::render_polygon),
        //std::make_pair("blur", API::render_blur)
    });

    std::vector<std::pair<std::string, LuaMultiValue_t>> SFML_STYLES;
    constexpr std::array<std::string_view, 2> SFML_STYLES_NAME = { "Default", "Fullscreen" };

    for (int i = 0, size = SFML_STYLES_NAME.size(); i < size; ++i)
        SFML_STYLES.emplace_back(std::make_pair(SFML_STYLES_NAME[i], lua_Number(i)));

    lhelper::register_table(lua_state, "styles", SFML_STYLES);

    lhelper::register_table(lua_state, "window", {
        std::make_pair("set_visible", API::window_set_visible),
        std::make_pair("is_open", API::window_is_open),
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
        std::make_pair("set_icon", API::window_set_icon),
        std::make_pair("set_style", API::window_set_style)
    });

    std::vector<std::pair<std::string, LuaMultiValue_t>> SFML_KEYS;
    constexpr std::array<std::string_view, 101> SFML_KEYS_NAME = { "A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z","Num0","Num1","Num2","Num3","Num4","Num5","Num6","Num7","Num8","Num9","Escape","LControl","LShift","LAlt","LSystem","RControl","RShift","RAlt","RSystem","Menu","LBracket","RBracket","Semicolon","Comma","Period","Quote","Slash","Backslash","Tilde","Equal","Hyphen","Space","Enter","Backspace","Tab","PageUp","PageDown","End","Home","Insert","Delete","Add","Subtract","Multiply","Divide","Left","Right","Up","Down","Numpad0","Numpad1","Numpad2","Numpad3","Numpad4","Numpad5","Numpad6","Numpad7","Numpad8","Numpad9","F1","F2","F3","F4","F5","F6","F7","F8","F9","F10","F11","F12","F13","F14","F15","Pause" };

    for (int i = 0, size = SFML_KEYS_NAME.size(); i < size; ++i)
        SFML_KEYS.emplace_back(std::make_pair(SFML_KEYS_NAME[i], lua_Number(i)));

    SFML_KEYS.emplace_back(std::make_pair("Dash", 56));
    SFML_KEYS.emplace_back(std::make_pair("BackSpace", 59));
    SFML_KEYS.emplace_back(std::make_pair("BackSlash", 53));
    SFML_KEYS.emplace_back(std::make_pair("Semicolon", 48));
    SFML_KEYS.emplace_back(std::make_pair("Return", 58));

    lhelper::register_table(lua_state, "keys", SFML_KEYS);

    lhelper::register_table(lua_state, "keyboard", {
        std::make_pair("get_pressed", API::keyboard_get_pressed),
        std::make_pair("is_pressed", API::keyboard_is_pressed),
    });

    std::vector<std::pair<std::string, LuaMultiValue_t>> SFML_BUTTONS;
    constexpr std::array<std::string_view, 5> SFML_BUTTONS_NAME = { "Left", "Right", "Middle", "XButton1", "XButton2" };

    for (int i = 0, size = SFML_BUTTONS_NAME.size(); i < size; ++i)
        SFML_BUTTONS.emplace_back(std::make_pair(SFML_BUTTONS_NAME[i], lua_Number(i)));

    lhelper::register_table(lua_state, "buttons", SFML_BUTTONS);

    lhelper::register_table(lua_state, "mouse", {
        std::make_pair("get_pressed", API::mouse_get_pressed),
        std::make_pair("is_pressed", API::mouse_is_pressed),
        std::make_pair("is_scrolling_up", API::mouse_is_scrolling_up),
        std::make_pair("is_scrolling_down", API::mouse_is_scrolling_down),
    });

    std::vector<std::pair<std::string, LuaMultiValue_t>> SFML_CURSORS;
    constexpr std::array<std::string_view, 21> SFML_CURSORS_NAME = { "Arrow", "ArrowWait", "Wait", "Text", "Hand", "SizeHorizontal", "SizeVertical", "SizeTopLeftBottomRight", "SizeBottomLeftTopRight", "SizeLeft", "SizeRight", "SizeTop", "SizeBottom", "SizeTopLeft", "SizeBottomRight", "SizeBottomLeft", "SizeTopRight", "SizeAll", "Cross", "Help", "NotAllowed" };

    for (int i = 0, size = SFML_CURSORS_NAME.size(); i < size; ++i)
        SFML_CURSORS.emplace_back(std::make_pair(SFML_CURSORS_NAME[i], lua_Number(i)));

    lhelper::register_table(lua_state, "cursors", SFML_CURSORS);

    lhelper::register_table(lua_state, "cursor", {
        std::make_pair("get_pos", API::cursor_get_pos),
        std::make_pair("is_bound", API::cursor_is_bound),
        std::make_pair("in_window", API::cursor_in_window),
        std::make_pair("change_type", API::cursor_change_type),
    });

    lhelper::register_table(lua_state, "file", {
        std::make_pair("read", API::file_read),
        std::make_pair("write", API::file_write),
        std::make_pair("create", API::file_create),
        std::make_pair("remove", API::file_remove),
        std::make_pair("copy", API::file_copy),
        std::make_pair("exists", API::file_exists),
        std::make_pair("line_count", API::file_line_count),
        std::make_pair("clear", API::file_clear),
        std::make_pair("rename", API::file_rename),
        std::make_pair("get_list", API::file_get_list),
    });

    lhelper::register_table(lua_state, "cmath", {
        std::make_pair("rand_int", API::rand_int),
        std::make_pair("rand_double", API::rand_double),
        std::make_pair("lerp", API::lerp),
        std::make_pair("clamp", API::clamp),
        std::make_pair("round", API::round),
    });
    
    lhelper::register_table(lua_state, "globalvars", {
        std::make_pair("get_executable_path", API::get_executable_path),
        std::make_pair("get_os_name", API::get_os_name),
        std::make_pair("get_args", API::get_args),
    });

    lhelper::register_table(lua_state, "network", {
        std::make_pair("bind", API::network_bind),
        std::make_pair("unbind", API::network_unbind),
        std::make_pair("send", API::network_send),
        std::make_pair("receive", API::network_receive),
        std::make_pair("get_local_address", API::network_get_local_address)
    });

    lhelper::register_table(lua_state, "hotreload", {
        std::make_pair("get_state", API::get_state),
        std::make_pair("set_state", API::set_state),
        std::make_pair("reload", API::reload),
    });

    lhelper::register_class<API::Font>(lua_state, "Font");
    lhelper::register_class<API::Vector2>(lua_state, "Vector2");
    lhelper::register_class<API::Color>(lua_state, "Color");
    lhelper::register_class<API::Sound>(lua_state, "Sound");
    lhelper::register_class<API::Sprite>(lua_state, "Sprite");
    lhelper::register_class<API::View>(lua_state, "View");
}