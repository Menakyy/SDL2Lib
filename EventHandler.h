#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "Point.h"

#include <SDL2/SDL.h>

class EventHandler
{
public:
    EventHandler();
    ~EventHandler();

    int       pollEvent();
    SDL_Event getEvent() const;

    bool        isTextInput() const;
    bool        isQuit() const;
    bool        isKeyDown() const;
    bool        isKeyUp() const;
    SDL_Keycode getKeyCode() const;

    bool  isMouseButtonDown() const;
    bool  isMouseButtonUp() const;
    void  getMousePosition(int& x, int& y) const;
    Point getMousePosition() const;

    bool isPointInsideRect(const Point& point, const SDL_Rect& rect) const;

    bool  isWindowEvent() const;
    Uint8 getWindowEvent() const;

    bool isShiftPressed() const;
    bool isCtrlPressed() const;
    bool isAltPressed() const;

    bool isKeyPressed(SDL_Keycode key) const;

    const Uint8* getKeyboardState() const;

    void injectEvent(const SDL_Event& e);

private:
    SDL_Event event;
};

#endif  // EVENT_HANDLER_H