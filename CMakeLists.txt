cmake_minimum_required(VERSION 3.5)
project("SDL_Project")

include(CTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

option(CLANG_TIDY "Enable clang-tidy checks." OFF)
option(ENABLE_VALGRIND "Enable Valgrind for tests." OFF)
option(TESTS "Enable tests." OFF)
option(CODE_COVERAGE "Enable code coverage output generation" OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
endif()

if(ENABLE_VALGRIND)
    find_program(VALGRIND_EXECUTABLE valgrind)

    if(NOT VALGRIND_EXECUTABLE)
        message(FATAL_ERROR "Valgrind not found. Please install Valgrind.")
    else()
        add_compile_definitions(CPPUTEST_MEM_LEAK_DETECTION_DISABLED)
    endif()
endif()

include_directories("lib/" "./")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_library(SDL_Lib STATIC
    "SDLSystem.cpp"
    "Window.cpp"
    "Renderer.cpp"
    "TextField.cpp"
    "FontManager.cpp"
    "Image.cpp"
    "Point.cpp"
    "Size.cpp"
    "Line.cpp"
    "View.cpp"
    "Container.cpp"
    "Color.cpp"
    "Rectangle.cpp"
    "EventHandler.cpp"
    "TextInput.cpp"
    "ShapeView.cpp"
    "Logger.cpp"
    "Widget.cpp"
    "Utilities.cpp"
    "Button.cpp"
    "AbstractCallback.cpp"
    "SoundManager.cpp"
    "ScreenManager.cpp"
)

add_executable(${PROJECT_NAME}  "main.cpp")
target_link_libraries(${PROJECT_NAME}  SDL_Lib)

if(CODE_COVERAGE)
    target_compile_options(${PROJECT_NAME} PUBLIC --coverage)
    target_link_options(${PROJECT_NAME} PUBLIC --coverage)
    add_custom_command(
        TARGET ${PROJECT_NAME} PRE_BUILD COMMAND
        find ${CMAKE_BINARY_DIR} -type f -name "*.gcda" -exec rm {} +
    )
endif()

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} SDL2_ttf SDL2_image SDL2_mixer)

if(CLANG_TIDY)
    set_target_properties(${PROJECT_NAME} PROPERTIES CXX_CLANG_TIDY "clang-tidy")
endif()

if(TESTS)
    add_subdirectory("lib/cpputest")
    add_subdirectory("tests")
endif(TESTS)

message("
    Project Name:           ${PROJECT_NAME}
    CMAKE_MAKE_PROGRAM:     ${CMAKE_MAKE_PROGRAM}
    CMAKE_C_COMPILER:       ${CMAKE_C_COMPILER}
    CMAKE_CXX_COMPILER:     ${CMAKE_CXX_COMPILER}
    CMAKE_BUILD_TYPE:       ${CMAKE_BUILD_TYPE}
    SDL2_INCLUDE_DIRS:      ${SDL2_INCLUDE_DIRS}
    SDL2_LIBRARIES:         ${SDL2_LIBRARIES}
    CMAKE_CXX_STANDARD:     ${CMAKE_CXX_STANDARD}
    TESTS:                  ${TESTS}
    CLANG_TIDY:             ${CLANG_TIDY}
    ENABLE_VALGRIND:        ${ENABLE_VALGRIND}
    CODE_COVERAGE:          ${CODE_COVERAGE}
    CMAKE_CXX_FLAGS:        ${CMAKE_CXX_FLAGS}
    "
)