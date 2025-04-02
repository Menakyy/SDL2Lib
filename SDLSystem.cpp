#include "SDLSystem.h"

#include "Logger.h"

SDLSystem::SDLSystem(Uint32 sdlInitFlags, InitOptions initOptions, AudioParameters audioParameters)
    : sdlInitFlags(sdlInitFlags),
      audioParameters(audioParameters),
      initOptions(initOptions)
{
    bool initSuccess = true;

    if (SDL_Init(sdlInitFlags) != 0)
    {
        Logger::error(("SDL_Init Error: " + std::string(SDL_GetError())).c_str());
        initSuccess = false;
    }

    if ((initOptions & ttf) != 0 && TTF_Init() == -1)
    {
        Logger::error(("TTF_Init Error: " + std::string(TTF_GetError())).c_str());
        initSuccess = false;
    }

    int mixInitCode = Mix_OpenAudio(audioParameters.frequency,
                                    audioParameters.format,
                                    audioParameters.channels,
                                    audioParameters.chunksize);

    if ((initOptions & audio) != 0 && mixInitCode == -1)
    {
        Logger::error(("Mix_OpenAudio Error: " + std::string(Mix_GetError())).c_str());
        initSuccess = false;
    }

    if (not initSuccess)
    {
        Logger::error("SDLSystem initialization failed");
        std::abort();
    }

    Logger::info("SDLSystem initialized");
}

SDLSystem::~SDLSystem()
{
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
}
