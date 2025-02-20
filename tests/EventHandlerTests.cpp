#include "EventHandler.h"
#include "Point.h"
#include "SDLSystem.h"

#include <CppUTest/TestHarness.h>
#include <SDL2/SDL.h>

TEST_GROUP(EventHandlerTest)
{
    SDLSystem*    sdlSystem    = nullptr;
    EventHandler* eventHandler = nullptr;

    void setup()
    {
        sdlSystem    = new SDLSystem(SDL_INIT_VIDEO);
        eventHandler = new EventHandler();
    }

    void teardown()
    {
        delete eventHandler;
        delete sdlSystem;
    }
};

TEST(EventHandlerTest, PollEvent)
{
    SDL_Event event;
    event.type = SDL_QUIT;
    SDL_PushEvent(&event);

    int result = eventHandler->pollEvent();
    CHECK_EQUAL(1, result);
}

TEST(EventHandlerTest, GetEvent)
{
    SDL_Event event;
    event.type = SDL_QUIT;
    SDL_PushEvent(&event);

    eventHandler->pollEvent();
    SDL_Event polledEvent = eventHandler->getEvent();
    CHECK_EQUAL(SDL_QUIT, polledEvent.type);
}

TEST(EventHandlerTest, IsTextInput)
{
    SDL_Event event;
    event.type = SDL_TEXTINPUT;
    SDL_PushEvent(&event);

    eventHandler->pollEvent();
    CHECK_TRUE(eventHandler->isTextInput());
}

TEST(EventHandlerTest, IsQuit)
{
    SDL_Event event;
    event.type = SDL_QUIT;
    SDL_PushEvent(&event);

    eventHandler->pollEvent();
    CHECK_TRUE(eventHandler->isQuit());
}

TEST(EventHandlerTest, IsKeyDown)
{
    SDL_Event event;
    event.type = SDL_KEYDOWN;
    SDL_PushEvent(&event);

    eventHandler->pollEvent();
    CHECK_TRUE(eventHandler->isKeyDown());
}

TEST(EventHandlerTest, IsKeyUp)
{
    SDL_Event event;
    event.type = SDL_KEYUP;
    SDL_PushEvent(&event);

    eventHandler->pollEvent();
    CHECK_TRUE(eventHandler->isKeyUp());
}

TEST(EventHandlerTest, GetKeyCode)
{
    SDL_Event event;
    event.type           = SDL_KEYDOWN;
    event.key.keysym.sym = SDLK_a;
    SDL_PushEvent(&event);

    eventHandler->pollEvent();
    CHECK_EQUAL(SDLK_a, eventHandler->getKeyCode());
}

TEST(EventHandlerTest, IsMouseButtonDown)
{
    SDL_Event event;
    event.type = SDL_MOUSEBUTTONDOWN;
    SDL_PushEvent(&event);

    eventHandler->pollEvent();
    CHECK_TRUE(eventHandler->isMouseButtonDown());
}

TEST(EventHandlerTest, IsMouseButtonUp)
{
    SDL_Event event;
    event.type = SDL_MOUSEBUTTONUP;
    SDL_PushEvent(&event);

    eventHandler->pollEvent();
    CHECK_TRUE(eventHandler->isMouseButtonUp());
}

TEST(EventHandlerTest, GetMousePosition)
{
    SDL_Event event;
    event.type     = SDL_MOUSEMOTION;
    event.motion.x = 100;
    event.motion.y = 200;
    SDL_PushEvent(&event);

    eventHandler->pollEvent();
    Point mousePos = eventHandler->getMousePosition();
    CHECK_EQUAL(100, mousePos.getX());
    CHECK_EQUAL(200, mousePos.getY());
}

TEST(EventHandlerTest, IsPointInsideRect)
{
    SDL_Rect rect = { 50, 50, 100, 100 };
    Point    pointInside(75, 75);
    Point    pointOutside(200, 200);

    CHECK_TRUE(eventHandler->isPointInsideRect(pointInside, rect));
    CHECK_FALSE(eventHandler->isPointInsideRect(pointOutside, rect));
}

TEST(EventHandlerTest, IsWindowEvent)
{
    SDL_Event event;
    event.type = SDL_WINDOWEVENT;
    SDL_PushEvent(&event);

    eventHandler->pollEvent();
    CHECK_TRUE(eventHandler->isWindowEvent());
}

TEST(EventHandlerTest, GetWindowEvent)
{
    SDL_Event event;
    event.type         = SDL_WINDOWEVENT;
    event.window.event = SDL_WINDOWEVENT_CLOSE;
    SDL_PushEvent(&event);

    eventHandler->pollEvent();
    CHECK_EQUAL(SDL_WINDOWEVENT_CLOSE, eventHandler->getWindowEvent());
}

TEST(EventHandlerTest, IsShiftPressed)
{
    SDL_SetModState(KMOD_SHIFT);
    CHECK_TRUE(eventHandler->isShiftPressed());
    SDL_SetModState(KMOD_NONE);
}

TEST(EventHandlerTest, IsCtrlPressed)
{
    SDL_SetModState(KMOD_CTRL);
    CHECK_TRUE(eventHandler->isCtrlPressed());
    SDL_SetModState(KMOD_NONE);
}

TEST(EventHandlerTest, IsAltPressed)
{
    SDL_SetModState(KMOD_ALT);
    CHECK_TRUE(eventHandler->isAltPressed());
    SDL_SetModState(KMOD_NONE);
}