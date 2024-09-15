cmake_minimum_required(VERSION 3.20)
project("GLTests")

include(CTest)

set(SRC_FILES
    "../SDLSystem.cpp"
    "../Window.cpp"
    "../Line.cpp"
    "../Image.cpp"
    "../TextField.cpp"
)

add_executable(${PROJECT_NAME}
    "testAppMain.cpp"
    "WindowTests.cpp"
    "LineTests.cpp"
    "ImageTests.cpp"
    "TextFieldTests.cpp"
    ${SRC_FILES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE "CppUTest" ${SDL2_LIBRARIES} "SDL2_ttf" "SDL2_image")

add_test(
    NAME "${PROJECT_NAME}"
    COMMAND "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TEST_EXECUTABLE}"
    ${CPPUTEST_ARGS}
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
)
