#include "EventHandler.h"

EventHandler::EventHandler()
{
}

EventHandler::~EventHandler()
{
}

bool EventHandler::pollEvent()
{
    return SDL_PollEvent(&event);
}

SDL_Event EventHandler::getEvent() const
{
    return event;
}

bool EventHandler::isQuit() const
{
    return event.type == SDL_QUIT;
}

bool EventHandler::isKeyDown() const
{
    return event.type == SDL_KEYDOWN;
}

bool EventHandler::isKeyUp() const
{
    return event.type == SDL_KEYUP;
}

SDL_Keycode EventHandler::getKeyCode() const
{
    if (isKeyDown() || isKeyUp())
    {
        return event.key.keysym.sym;
    }
    return 0;
}