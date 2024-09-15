#include "CppUTest/TestHarness.h"
#include "SDLSystem.h"
#include "Window.h"

TEST_GROUP(WindowTestsGroup)
{
    SDLSystem* sdlSystem = nullptr;
    Window*    window    = nullptr;

    void setup()
    {
        sdlSystem = new SDLSystem(SDL_INIT_VIDEO);

        window = new Window("TestWindow", 100, 100, 800, 600, SDL_WINDOW_SHOWN);
    }

    void teardown()
    {
        delete window;
        delete sdlSystem;
    }
};

TEST(WindowTestsGroup, WindowCreation)
{
    CHECK(window->getWindow() != nullptr);
}

TEST(WindowTestsGroup, SetSizeTest)
{
    size_t newWidth  = 1024;
    size_t newHeight = 768;

    window->setSize(newWidth, newHeight);

    size_t actualWidth, actualHeight;
    window->getSize(actualWidth, actualHeight);

    CHECK_EQUAL(newWidth, actualWidth);
    CHECK_EQUAL(newHeight, actualHeight);
}

TEST(WindowTestsGroup, GetSizeInitialTest)
{
    size_t width, height;

    window->getSize(width, height);

    CHECK_EQUAL(800, width);
    CHECK_EQUAL(600, height);
}
