#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <SDL2/SDL.h>

class EventHandler
{
public:
    EventHandler();
    ~EventHandler();

    bool      pollEvent();
    SDL_Event getEvent() const;

    bool        isTextInput() const;
    bool        isQuit() const;
    bool        isKeyDown() const;
    bool        isKeyUp() const;
    SDL_Keycode getKeyCode() const;

private:
    SDL_Event event;
};

#endif
