#ifndef INTERFACES_RENDERABLE
#define INTERFACES_RENDERABLE

#include <SDL2/SDL.h>

class Renderable
{
public:
    virtual ~Renderable() = default;

    virtual void render() const = 0;
    virtual void setRect(const SDL_Rect& rect) = 0;
};

#endif /* INTERFACES_RENDERABLE */
