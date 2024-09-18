cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(Moonshine VERSION 0.1.0 LANGUAGES C CXX)

if(NOT (CMAKE_SYSTEM_NAME STREQUAL "Linux") AND NOT (CMAKE_SYSTEM_NAME STREQUAL "Windows"))
    message(FATAL_ERROR "${CMAKE_SYSTEM_NAME} is not supported!")
endif()

set(CMAKE_CXX_STANDARD 17)

file(GLOB SGHeaders "headers/*.hpp")
source_group("Header Files" FILES ${SGHeaders})

file(GLOB SGHeaders_API "headers/API/*.hpp")
source_group("Header Files/API" FILES ${SGHeaders_API})

file(GLOB SGHeaders_API_Objects "headers/API/Objects/*.hpp")
source_group("Header Files/API/Objects" FILES ${SGHeaders_API_Objects})

file(GLOB SGHeaders_Custom_Shapes "headers/Custom Shapes/*.hpp")
source_group("Header Files/Custom Shapes" FILES ${SGHeaders_Custom_Shapes})

file(GLOB SGHeaders_Lua_Extensions "headers/Lua Extensions/*.hpp")
source_group("Header Files/Lua Extensions" FILES ${SGHeaders_Lua_Extensions})

file(GLOB SGHeaders_UI_Objects "headers/UI Objects/*.hpp")
source_group("Header Files/UI Objects" FILES ${SGHeaders_UI_Objects})

file(GLOB SGSources "sources/*.cpp")
source_group("Source Files" FILES ${SGSources})

file(GLOB SGSources_API_Objects "sources/API/Objects/*.cpp")
source_group("Source Files/API/Objects" FILES ${SGSources_API_Objects})

file(GLOB SGSources_Custom_Shapes "sources/Custom Shapes/*.cpp")
source_group("Source Files/Custom Shapes" FILES ${SGSources_Custom_Shapes})

file(GLOB SGSources_Lua_Extensions "sources/Lua Extensions/*.cpp")
source_group("Source Files/Lua Extensions" FILES ${SGSources_Lua_Extensions})

file(GLOB SGSources_UI_Objects "sources/UI Objects/*.cpp")
source_group("Source Files/UI Objects" FILES ${SGSources_UI_Objects})

file(GLOB SGResources "resources/*.hpp" "resources/icon.rc")
source_group("Resource Files" FILES ${SGResources})

add_executable(${PROJECT_NAME}
    ${SGHeaders}
    ${SGHeaders_API}
    ${SGHeaders_API_Objects}
    ${SGHeaders_Custom_Shapes}
    ${SGHeaders_Lua_Extensions}
    ${SGHeaders_UI_Objects}
    ${SGResources}
    ${SGSources}
    ${SGSources_API_Objects}
    ${SGSources_Custom_Shapes}
    ${SGSources_Lua_Extensions}
    ${SGSources_UI_Objects}

    resources/icon.rc
)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    find_package(SFML 2.6 COMPONENTS graphics system audio network REQUIRED)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(LuaJIT REQUIRED IMPORTED_TARGET luajit)

    target_link_libraries(${PROJECT_NAME} PRIVATE
        sfml-graphics sfml-system sfml-audio sfml-network
        PkgConfig::LuaJIT
    )

    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:RELEASE>:
            -O3
        >
        -Wextra
    )

    target_include_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/headers;"
        "${CMAKE_CURRENT_SOURCE_DIR}/headers/API;"
        "${CMAKE_CURRENT_SOURCE_DIR}/headers/API/Objects;"
        "${CMAKE_CURRENT_SOURCE_DIR}/headers/Custom Shapes;"
        "${CMAKE_CURRENT_SOURCE_DIR}/headers/Lua Extensions;"
        "${CMAKE_CURRENT_SOURCE_DIR}/headers/UI Objects;"
        "${CMAKE_CURRENT_SOURCE_DIR}/resources"
    )
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    if (NOT CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        message(FATAL_ERROR "At the moment, the build configuration for Windows supports only \"MSVS\", platform x86")
    endif()

    set(LIB_PATH_LuaJIT "D:/C++ Libs/LuaJIT")
    set(LIB_PATH_SFML "D:/C++ Libs/SFML")

    set(CMAKE_SUPPRESS_REGENERATION true)
    set(CMAKE_SKIP_PACKAGE_ALL_DEPENDENCY true)

    set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/$<CONFIG>/"
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
    )

    target_include_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/headers;"
        "${CMAKE_CURRENT_SOURCE_DIR}/headers/API;"
        "${CMAKE_CURRENT_SOURCE_DIR}/headers/API/Objects;"
        "${CMAKE_CURRENT_SOURCE_DIR}/headers/Custom Shapes;"
        "${CMAKE_CURRENT_SOURCE_DIR}/headers/Lua Extensions;"
        "${CMAKE_CURRENT_SOURCE_DIR}/headers/UI Objects;"
        "${CMAKE_CURRENT_SOURCE_DIR}/resources;"
        "${LIB_PATH_LuaJIT}/include;"
        "${LIB_PATH_SFML}/include"
    )

    target_compile_definitions(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:
            _DEBUG
        >
        $<$<CONFIG:Release>:
            NDEBUG;
            SFML_STATIC;
            _CRT_SECURE_NO_WARNINGS
        >
        WIN32;
        UNICODE;
        _UNICODE
    )

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
            /INCREMENTAL
        >
        $<$<CONFIG:Release>:
            /OPT:REF;
            /OPT:ICF;
            /INCREMENTAL:NO
        >
        /DEBUG
    )

    set(ADDITIONAL_LIBRARY_DEPENDENCIES
        $<$<CONFIG:Release>:
            sfml-graphics-s;
            sfml-window-s;
            sfml-system-s;
            sfml-audio-s;
            sfml-network-s;
            winmm;
            opengl32;
            freetype;
            gdi32;
            openal32;
            flac;
            vorbisenc;
            vorbisfile;
            vorbis;
            ogg;
            wldap32;
            ws2_32;
            crypt32;
            normaliz;
            lua51;
            luajit
        >
    )

    target_link_libraries(${PROJECT_NAME} PRIVATE ${ADDITIONAL_LIBRARY_DEPENDENCIES})

    target_link_directories(${PROJECT_NAME} PRIVATE
        "${LIB_PATH_LuaJIT}/x86/lib;"
        "${LIB_PATH_SFML}/x86/lib;"
    )
endif()
