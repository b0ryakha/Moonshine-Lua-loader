#include "Application.hpp"
inline Application* app = nullptr;

#ifdef _WIN32
    #include <windows.h>
#endif

int main(int argc, char** argv) {
    #ifdef _WIN32
        ShowWindow(GetConsoleWindow(), SW_HIDE);
    #endif
    
    app = Application::instance(argc, argv);
    
    return app->exec();
}