cmake_minimum_required(VERSION 3.20)
project("GLTests")
include(CTest)

find_program(VALGRIND_EXECUTABLE valgrind)

if(VALGRIND_EXECUTABLE)
    message(STATUS "Valgrind found: ${VALGRIND_EXECUTABLE}")
else()
    message(SEND_ERROR "Valgrind not found. Please install Valgrind.")
endif()

set(SRC_FILES
    "../Window.cpp"
    "../Color.cpp"
    "../Container.cpp"
    "../EventHandler.cpp"
    "../FontManager.cpp"
    "../Image.cpp"
    "../Line.cpp"
    "../Logger.cpp"
    "../Point.cpp"
    "../Rectangle.cpp"
    "../Renderer.cpp"
    "../SDLSystem.cpp"
    "../ShapeView.cpp"
    "../Size.cpp"
    "../TextField.cpp"
    "../TextInput.cpp"
    "../View.cpp"
    "../Utilities.cpp"
    "../Button.cpp"
    "../AbstractCallback.cpp"
    "../Widget.cpp"
)
add_executable(${PROJECT_NAME}
    "testAppMain.cpp"
    # "ImageTests.cpp"
    "RectangleTests.cpp"
    # "EventHandlerTests.cpp"
    # "TextFieldTests.cpp"
    ${SRC_FILES}
)

if(CODE_COVERAGE)
    target_compile_options(${PROJECT_NAME} PUBLIC --coverage)
    target_link_options(${PROJECT_NAME} PUBLIC --coverage)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE "CppUTest" ${SDL2_LIBRARIES} "SDL2_ttf" "SDL2_image")
set(CPPUTEST_ARGS "-o" "junit" "-v")

add_test(
    NAME "${PROJECT_NAME}"
    COMMAND "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}"
    ${CPPUTEST_ARGS}
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
)

if(ENABLE_VALGRIND AND VALGRIND_EXECUTABLE)
    add_test(
        NAME "${PROJECT_NAME}Valgrind"
        COMMAND valgrind
        --leak-check=full
        --show-leak-kinds=all
        --track-origins=yes
        --trace-children=yes
        #--verbose
        --log-file=logs/valgrind.log
        "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}"
        ${CPPUTEST_ARGS}
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
    )
endif()