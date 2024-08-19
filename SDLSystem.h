#ifndef SDLSYSTEM
#define SDLSYSTEM


#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class SDLSystem
{
public:
    SDLSystem(Uint32 sdlInitFlags);
    ~SDLSystem();

private:
    Uint32 sdlInitFlags = 0;
};


#endif /* SDLSYSTEM */
