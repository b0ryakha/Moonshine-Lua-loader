#include "Application.hpp"
inline Application* app = nullptr;

#ifdef _WIN32
    #include <windows.h>
    std::string font_path = "C:/WINDOWS/Fonts/";
#elif defined(__linux__)
    std::string font_path = "/usr/share/fonts/TTF/";
#endif

int main(int argc, char** argv) {
    #ifdef _WIN32
        ShowWindow(GetConsoleWindow(), SW_HIDE);
    #endif
    
    app = Application::instance(argc, argv);

    return app->exec();
}