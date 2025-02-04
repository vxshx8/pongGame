cmake_minimum_required(VERSION 3.10)
cmake_policy(SET CMP0115 NEW)
project(pongGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(IMGUI_SOURCES
    ${CMAKE_SOURCE_DIR}/../include/imgui/imgui.cpp
    ${CMAKE_SOURCE_DIR}/../include/imgui/imgui_demo.cpp
    ${CMAKE_SOURCE_DIR}/../include/imgui/imgui_draw.cpp
    ${CMAKE_SOURCE_DIR}/../include/imgui/imgui_tables.cpp
    ${CMAKE_SOURCE_DIR}/../include/imgui/imgui_widgets.cpp
    ${CMAKE_SOURCE_DIR}/../include/imgui/imgui_impl_sdl2.cpp
    ${CMAKE_SOURCE_DIR}/../include/imgui/imgui_impl_sdlrenderer2.cpp
)

file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR}/Release)

include_directories(
    ${CMAKE_SOURCE_DIR}/../include      
    ${CMAKE_SOURCE_DIR}/../include/SDL2
    ${CMAKE_SOURCE_DIR}/../include/imgui
    ${CMAKE_SOURCE_DIR}/../include/TTF
)

link_directories(${CMAKE_SOURCE_DIR}/../lib/x64)

file(GLOB_RECURSE SOURCES src/*.cpp)
add_executable(MeuPrograma src/main.cpp src/renderer.cpp src/game.cpp ${IMGUI_SOURCES})



target_link_libraries(MeuPrograma SDL2 SDL2main SDL2_ttf)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)