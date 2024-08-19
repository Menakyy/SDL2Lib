#include "SDLSystem.h"

#include <iostream>

SDLSystem::SDLSystem(Uint32 sdlInitFlags) : sdlInitFlags(sdlInitFlags)
{
    if (SDL_Init(sdlInitFlags) != 0)
    {
        throw std::runtime_error("SDL_Init Error: " + std::string(SDL_GetError()));
    }

    if (TTF_Init() == -1)
    {
        throw std::runtime_error("TTF_Init Error: " + std::string(TTF_GetError()));
    }
}

SDLSystem::~SDLSystem()
{
    TTF_Quit();
    SDL_Quit();
}
