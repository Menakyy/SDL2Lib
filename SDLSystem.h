#ifndef SDLSYSTEM
#define SDLSYSTEM


#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

class SDLSystem
{
public:
    struct AudioParameters
    {
        int    frequency;
        Uint16 format;
        int    channels;
        int    chunksize;
    };

    enum InitOptions
    {
        none  = 0,
        ttf   = 1 << 0,
        audio = 1 << 1,
    };

    SDLSystem(Uint32          sdlInitFlags,
              InitOptions     initOptions     = none,
              AudioParameters audioParameters = { 44100, MIX_DEFAULT_FORMAT, 2, 2048 });
    ~SDLSystem();


private:
    Uint32          sdlInitFlags    = 0;
    AudioParameters audioParameters = { 0, 0, 0, 0 };
    InitOptions     initOptions     = none;
};


#endif /* SDLSYSTEM */
