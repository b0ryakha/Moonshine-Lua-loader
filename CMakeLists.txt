cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(Moonshine CXX)

set(CMAKE_SUPPRESS_REGENERATION true)
set(CMAKE_SKIP_INSTALL_ALL_DEPENDENCY true)
set(CMAKE_SKIP_PACKAGE_ALL_DEPENDENCY true)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

set(LIB_PATH_LuaJIT "D:/C++ Libs/LuaJIT")
set(LIB_PATH_SFML "D:/C++ Libs/SFML")
set(LIB_PATH_CURL "D:/C++ Libs/CURL")

if (NOT ("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86") AND NOT ("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32"))
    message(FATAL_ERROR "${CMAKE_VS_PLATFORM_NAME} is not supported!")
endif()

set(CMAKE_CONFIGURATION_TYPES
    "Release"
    "Debug"
    CACHE STRING "" FORCE
)

#remove default flags provided with CMake for MSVC
if (MSVC)
    set(CMAKE_CXX_FLAGS "")
    set(CMAKE_CXX_FLAGS_DEBUG "")
    set(CMAKE_CXX_FLAGS_RELEASE "")

    set(CMAKE_EXE_LINKER_FLAGS "")
    set(CMAKE_MODULE_LINKER_FLAGS "")
    set(CMAKE_SHARED_LINKER_FLAGS "")
    set(CMAKE_STATIC_LINKER_FLAGS "")
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_MODULE_LINKER_FLAGS_DEBUG "${CMAKE_MODULE_LINKER_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "${CMAKE_SHARED_LINKER_FLAGS}")
    set(CMAKE_STATIC_LINKER_FLAGS_DEBUG "${CMAKE_STATIC_LINKER_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_MODULE_LINKER_FLAGS_RELEASE "${CMAKE_MODULE_LINKER_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS}")
    set(CMAKE_STATIC_LINKER_FLAGS_RELEASE "${CMAKE_STATIC_LINKER_FLAGS}")
endif()

file(GLOB Header_Files "headers/*.hpp")
source_group("Header Files" FILES ${Header_Files})

file(GLOB Header_Files__API "headers/API/*.hpp")
source_group("Header Files/API" FILES ${Header_Files__API})

file(GLOB Header_Files__API__Objects "headers/API/Objects/*.hpp")
source_group("Header Files/API/Objects" FILES ${Header_Files__API__Objects})

file(GLOB Header_Files__Custom_Shapes "headers/Custom Shapes/*.hpp")
source_group("Header Files/Custom Shapes" FILES ${Header_Files__Custom_Shapes})

file(GLOB Header_Files__Lua_Extensions "headers/Lua Extensions/*.hpp")
source_group("Header Files/Lua Extensions" FILES ${Header_Files__Lua_Extensions})

file(GLOB Header_Files__UI_Objects "headers/UI Objects/*.hpp")
source_group("Header Files/UI Objects" FILES ${Header_Files__UI_Objects})

file(GLOB Resource_Files "resources/*.hpp" "resources/icon.rc")
source_group("Resource Files" FILES ${Resource_Files})

file(GLOB Source_Files "sources/*.cpp")
source_group("Source Files" FILES ${Source_Files})

file(GLOB Source_Files__API__Objects "sources/API/Objects/*.cpp")
source_group("Source Files/API/Objects" FILES ${Source_Files__API__Objects})

file(GLOB Source_Files__Custom_Shapes "sources/Custom Shapes/*.cpp")
source_group("Source Files/Custom Shapes" FILES ${Source_Files__Custom_Shapes})

file(GLOB Source_Files__Lua_Extensions "sources/Lua Extensions/*.cpp")
source_group("Source Files/Lua Extensions" FILES ${Source_Files__Lua_Extensions})

file(GLOB Source_Files__UI_Objects "sources/UI Objects/*.cpp")
source_group("Source Files/UI Objects" FILES ${Source_Files__UI_Objects})

set(ALL_FILES
    ${Header_Files}
    ${Header_Files__API}
    ${Header_Files__API__Objects}
    ${Header_Files__Custom_Shapes}
    ${Header_Files__Lua_Extensions}
    ${Header_Files__UI_Objects}
    ${Resource_Files}
    ${Source_Files}
    ${Source_Files__API__Objects}
    ${Source_Files__Custom_Shapes}
    ${Source_Files__Lua_Extensions}
    ${Source_Files__UI_Objects}
)

add_executable(${PROJECT_NAME} ${ALL_FILES} resources/icon.rc)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/$<CONFIG>/"
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
)

target_include_directories(${PROJECT_NAME} PUBLIC
    "$<$<CONFIG:Release>:"
        "${CMAKE_CURRENT_SOURCE_DIR}/headers;"
        "${CMAKE_CURRENT_SOURCE_DIR}/headers/API;"
        "${CMAKE_CURRENT_SOURCE_DIR}/headers/API/Objects;"
        "${CMAKE_CURRENT_SOURCE_DIR}/headers/Custom Shapes;"
        "${CMAKE_CURRENT_SOURCE_DIR}/headers/Lua Extensions;"
        "${CMAKE_CURRENT_SOURCE_DIR}/headers/UI Objects;"
        "${LIB_PATH_LuaJIT}/include;"
        "${LIB_PATH_SFML}/include;"
        "${LIB_PATH_CURL}/include;"
        "${CMAKE_CURRENT_SOURCE_DIR}/resources"
    ">"
)    

target_compile_definitions(${PROJECT_NAME} PRIVATE
    "$<$<CONFIG:Debug>:"
        "_DEBUG"
    ">"
    "$<$<CONFIG:Release>:"
        "NDEBUG;"
        "SFML_STATIC;"
        "CURL_STATICLIB;"
        "_CRT_SECURE_NO_WARNINGS"
    ">"
    "WIN32;"
    "UNICODE;"
    "_UNICODE"
)

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:
            /O2;
            /Gy
        >
        /permissive-;
        /std:c++17;
        /sdl;
        /W3;
        ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
        ${DEFAULT_CXX_EXCEPTION_HANDLING}
    )
    
    target_link_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:
            /SUBSYSTEM:CONSOLE;
            /INCREMENTAL
        >
        $<$<CONFIG:Release>:
            /SUBSYSTEM:WINDOWS;
            /OPT:REF;
            /OPT:ICF;
            /INCREMENTAL:NO
        >
        /DEBUG
    )
endif()

set (ADDITIONAL_LIBRARY_DEPENDENCIES
    "$<$<CONFIG:Release>:"
        "sfml-graphics-s;"
        "sfml-window-s;"
        "sfml-system-s;"
        "sfml-audio-s;"
        "sfml-network-s;"
        "winmm;"
        "opengl32;"
        "freetype;"
        "gdi32;"
        "openal32;"
        "flac;"
        "vorbisenc;"
        "vorbisfile;"
        "vorbis;"
        "ogg;"
        "wldap32;"
        "ws2_32;"
        "crypt32;"
        "normaliz;"
        "libcurl_a;"
        "lua51;"
        "luajit"
    ">"
)

target_link_libraries(${PROJECT_NAME} PRIVATE "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

target_link_directories(${PROJECT_NAME} PRIVATE
    "$<$<CONFIG:Release>:"
        "${LIB_PATH_LuaJIT}/x86/lib;"
        "${LIB_PATH_SFML}/x86/lib;"
        "${LIB_PATH_CURL}/x86/lib"
    ">"
)