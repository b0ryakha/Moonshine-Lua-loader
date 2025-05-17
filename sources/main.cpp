#include "Application.hpp"

#ifdef _WIN32
#include <windows.h>
#endif

int main(int argc, char** argv) {
    #ifdef _WIN32
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    #endif

    return Application::instance(argc, argv)->exec();
}