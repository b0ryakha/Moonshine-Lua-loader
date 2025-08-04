cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(Moonshine VERSION 0.1.0 LANGUAGES C CXX)

if(NOT (CMAKE_SYSTEM_NAME STREQUAL "Linux") AND NOT (CMAKE_SYSTEM_NAME STREQUAL "Windows"))
    message(FATAL_ERROR "${CMAKE_SYSTEM_NAME} is not supported!")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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
    set(LuaJIT_PATH "D:/C++ Libs/LuaJIT")
    set(SFML_PATH "D:/C++ Libs/SFML")

    if (CMAKE_CL_64)
        set(CMAKE_GENERATOR_PLATFORM x64)
    else()
        set(CMAKE_GENERATOR_PLATFORM x86)
    endif()

    if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        message(WARNING "At the moment, the build configuration for Windows using clang supports only the x64 platform.")
        set(CMAKE_GENERATOR_PLATFORM x64)
    endif()

    set(CMAKE_SKIP_PACKAGE_ALL_DEPENDENCY true)

    target_include_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/headers"
        "${CMAKE_CURRENT_SOURCE_DIR}/headers/API"
        "${CMAKE_CURRENT_SOURCE_DIR}/headers/API/Objects"
        "${CMAKE_CURRENT_SOURCE_DIR}/headers/Custom Shapes"
        "${CMAKE_CURRENT_SOURCE_DIR}/headers/Lua Extensions"
        "${CMAKE_CURRENT_SOURCE_DIR}/headers/UI Objects"
        "${CMAKE_CURRENT_SOURCE_DIR}/resources"
        "${LuaJIT_PATH}/include"
        "${SFML_PATH}/include"
    )

    target_link_directories(${PROJECT_NAME} PRIVATE
        "${LuaJIT_PATH}/${CMAKE_GENERATOR_PLATFORM}/lib"
        "${SFML_PATH}/${CMAKE_GENERATOR_PLATFORM}/lib"
    )

    target_compile_definitions(${PROJECT_NAME} PRIVATE
        _CRT_SECURE_NO_WARNINGS
        SFML_STATIC
    )

    target_link_libraries(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:
            sfml-graphics-s-d
            sfml-window-s-d
            sfml-system-s-d
            sfml-audio-s-d
            sfml-network-s-d
        >
        $<$<CONFIG:Release>:
            sfml-graphics-s
            sfml-window-s
            sfml-system-s
            sfml-audio-s
            sfml-network-s
        >

        winmm
        opengl32
        freetype
        gdi32
        flac
        vorbisenc
        vorbisfile
        vorbis
        ogg
        wldap32
        ws2_32
        crypt32
        normaliz

        lua51 luajit
    )
endif()
