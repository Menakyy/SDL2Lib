#ifndef SCREEN_H
#define SCREEN_H

#include "Container.h"
#include "EventHandler.h"
#include "Renderer.h"

class Screen
{
public:
    virtual ~Screen() = default;

    virtual void init()                                               = 0;
    virtual void handleEvents(EventHandler& eventHandler, bool& exit) = 0;
    virtual void update()                                             = 0;
    virtual void render(Renderer& renderer)                           = 0;
};

#endif  // SCREEN_H