<img src="resources/icon.ico" align="right" width="150" />

## Moonshine ![STABLE](https://img.shields.io/static/v1?label=stage&message=stable&color=blue)
> A loader for lua scripts with custom API.

The API includes the ability to render, interact with files, window, sound, etc.

---

## API documentation
For information about the API, see [Documentation.md](Documentation.md) file.  
For comfortable use, recommended to download [snippets.json](snippets.json) (VS Code).

## Code examples
You can view code examples using the API in [Examples.md](Examples.md) file

## Building
### Built with:
- [SFML 3.0.0](https://www.sfml-dev.org) - Graphics and sound engine
- [LuaJIT 2.1](https://luajit.org/luajit.html) - Binding Lua and C++

#### Windows:
##### For Windows used <u>static libraries</u>, so before building, change the library paths to your own in CMakeLists.txt:
```cmake
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(LIB_PATH_LuaJIT "")
    set(LIB_PATH_SFML "")
...
```
##### Build:
```sh
cd Moonshine-Lua-loader
cmake -B "build" -G "Visual Studio 17 2022" -A "Win32"
cmake --build "build" --config Release
```
#### Arch Linux:
##### For Linux used <u>dynamic libraries</u>, so install them and other dependencies via the console:
```sh
sudo pacman -S cmake pkg-config sfml luajit clang
```
##### Build:
```sh
cd Moonshine-Lua-loader
cmake -B "build" -G "Unix Makefiles" -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER=clang
cmake --build "build" --config Release
```
##### The build is complete, but don't forget to install tf-ms-fonts for runtime.

## License
This project is licensed under the GNU GPLv3 License - see the [LICENSE.md](LICENSE.md) file for details
