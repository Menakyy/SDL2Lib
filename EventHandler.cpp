#include "EventHandler.h"

EventHandler::EventHandler()
{
}

EventHandler::~EventHandler()
{
}

int EventHandler::pollEvent()
{
    return SDL_PollEvent(&event);
}

SDL_Event EventHandler::getEvent() const
{
    return event;
}

bool EventHandler::isTextInput() const
{
    return event.type == SDL_TEXTINPUT;
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

bool EventHandler::isMouseButtonDown() const
{
    return event.type == SDL_MOUSEBUTTONDOWN;
}

bool EventHandler::isMouseButtonUp() const
{
    return event.type == SDL_MOUSEBUTTONUP;
}

void EventHandler::getMousePosition(int& x, int& y) const
{
    if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP)
    {
        x = event.motion.x;
        y = event.motion.y;
    }
}

Point EventHandler::getMousePosition() const
{
    Point point = Point(event.motion.x, event.motion.y);
    return point;
}

bool EventHandler::isPointInsideRect(const Point& point, const SDL_Rect& rect) const
{
    bool status = point.getX() >= rect.x && point.getX() <= rect.x + rect.w && point.getY() >= rect.y
                  && point.getY() <= rect.y + rect.h;

    return status;
}

bool EventHandler::isWindowEvent() const
{
    return event.type == SDL_WINDOWEVENT;
}

Uint8 EventHandler::getWindowEvent() const
{
    if (isWindowEvent())
    {
        return event.window.event;
    }
    return 0;
}

bool EventHandler::isShiftPressed() const
{
    return (SDL_GetModState() & KMOD_SHIFT) != 0;
}

bool EventHandler::isCtrlPressed() const
{
    return (SDL_GetModState() & KMOD_CTRL) != 0;
}

bool EventHandler::isAltPressed() const
{
    return (SDL_GetModState() & KMOD_ALT) != 0;
}

void EventHandler::injectEvent(const SDL_Event& e)
{
    event = e;
}
