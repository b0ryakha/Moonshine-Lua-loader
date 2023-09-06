cmake -B "build" -G "Visual Studio 17 2022" -A "Win32"
cmake --build "build" --config Release

rd /s /q "./build/CMakeFiles"
rd /s /q "./build/Win32"
del /q "build\ALL_BUILD.*"