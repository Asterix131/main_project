cmake_minimum_required(VERSION 3.24)
project(skin_studio VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

include(FetchContent)

# SDL3
FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-3.2.8
)

# Dear ImGui (docking branch)
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG docking
)

# JSON library for presets
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
)

FetchContent_MakeAvailable(SDL3 imgui nlohmann_json)

set(IMGUI_DIR ${imgui_SOURCE_DIR})

add_library(imgui_backend STATIC
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_sdl3.cpp
    ${IMGUI_DIR}/backends/imgui_impl_sdlrenderer3.cpp
)

target_include_directories(imgui_backend PUBLIC
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
)

target_link_libraries(imgui_backend PUBLIC SDL3::SDL3)

add_executable(skin_studio
    src/main.cpp
    src/app/App.cpp
    src/ui/Theme.cpp
    src/ui/Windows/CatalogWindow.cpp
    src/ui/Windows/EditorWindow.cpp
    src/data/SkinRepository.cpp
)

target_include_directories(skin_studio PRIVATE src)

target_link_libraries(skin_studio PRIVATE
    SDL3::SDL3
    imgui_backend
    nlohmann_json::nlohmann_json
)

if(WIN32)
    add_custom_command(TARGET skin_studio POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/assets
            $<TARGET_FILE_DIR:skin_studio>/assets
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/config
            $<TARGET_FILE_DIR:skin_studio>/config
    )
endif()
