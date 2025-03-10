#include "SDLSystem.h"
#include "Logger.h"

SDLSystem::SDLSystem(Uint32 sdlInitFlags) : sdlInitFlags(sdlInitFlags)
{
    if (SDL_Init(sdlInitFlags) != 0)
    {
        Logger::error(("SDL_Init Error: " + std::string(SDL_GetError())).c_str());
    }

    if (TTF_Init() == -1)
    {
        Logger::error(("TTF_Init Error: " + std::string(TTF_GetError())).c_str());
    }
}

SDLSystem::~SDLSystem()
{
    TTF_Quit();
    SDL_Quit();
}
