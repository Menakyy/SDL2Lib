#include "SoundManager.h"

#include "Logger.h"

SoundManager::SoundManager() : music(nullptr)
{
}

SoundManager::~SoundManager()
{
    cleanup();
}

void SoundManager::cleanup()
{
    for (auto& sound : sounds)
    {
        Mix_FreeChunk(sound.second);
    }
    sounds.clear();

    if (music != nullptr)
    {
        Mix_FreeMusic(music);
        music = nullptr;
    }

    // Mix_CloseAudio();
}

bool SoundManager::loadSound(const std::string& id, const std::string& filename)
{
    Mix_Chunk* sound = Mix_LoadWAV(filename.c_str());
    if (sound == nullptr)
    {
        Logger::error(
            ("Failed to load sound: " + filename + " SDL_mixer Error: " + std::string(Mix_GetError())).c_str());
        return false;
    }
    Logger::info(("Sound loaded: " + filename).c_str());
    sounds[id] = sound;
    return true;
}

void SoundManager::playSound(const std::string& id)
{
    auto it = sounds.find(id);
    if (it == sounds.end())
    {
        Logger::error(("Sound not found: " + id).c_str());
        return;
    }

    Logger::info(("Playing sound: " + id).c_str());
    Mix_PlayChannel(-1, sounds[id], 0);
}

void SoundManager::playMusic(const std::string& filename)
{
    if (music != nullptr)
    {
        Mix_FreeMusic(music);
    }
    music = Mix_LoadMUS(filename.c_str());
    if (music == nullptr)
    {
        Logger::error(
            ("Failed to load music: " + filename + " SDL_mixer Error: " + std::string(Mix_GetError())).c_str());
        return;
    }
    Logger::info(("Playing music: " + filename).c_str());
    Mix_PlayMusic(music, -1);
}

bool SoundManager::isSoundPlaying(const std::string& id)
{
    auto it = sounds.find(id);
    if (it == sounds.end())
    {
        Logger::error(("Sound not found: " + id).c_str());
        return false;
    }

    for (int channel = 0; channel < Mix_AllocateChannels(-1); ++channel)
    {
        bool status = Mix_Playing(channel) >= 0;
        if (Mix_GetChunk(channel) == it->second && status)
        {
            return true;
        }
    }

    return false;
}

void SoundManager::stopSound(const std::string& id)
{
    auto it = sounds.find(id);
    if (it == sounds.end())
    {
        Logger::error(("Sound not found: " + id).c_str());
        return;
    }

    for (int channel = 0; channel < Mix_AllocateChannels(-1); ++channel)
    {
        if (Mix_GetChunk(channel) == it->second)
        {
            Mix_HaltChannel(channel);
        }
    }
}

bool SoundManager::isMusicPlaying()
{
    return Mix_PlayingMusic() == 1;
}