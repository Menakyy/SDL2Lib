cmake_minimum_required(VERSION 3.0)
project("SDL_Project")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(${PROJECT_NAME}
    "main.cpp"
    "SDLSystem.cpp"
    "Window.cpp"
    "Renderer.cpp"
    "TextField.cpp"
    "FontManager.cpp"
    "Image.cpp")

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} SDL2_ttf SDL2_image)

message(
    "CMAKE_C_COMPILER:      ${CMAKE_C_COMPILER}\n"
    "CMAKE_CXX_COMPILER:    ${CMAKE_CXX_COMPILER}\n"
    "SDL2_INCLUDE_DIRS:     ${SDL2_INCLUDE_DIRS}\n"
    "SDL2_LIBRARIES:        ${SDL2_LIBRARIES}\n"
)