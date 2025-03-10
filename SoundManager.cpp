#include "SoundManager.h"

#include "Logger.h"

std::unordered_map<std::string, Mix_Chunk*> SoundManager::sounds;
Mix_Music*                                  SoundManager::music = nullptr;

bool SoundManager::init()
{
    if (Mix_OpenAudio(kDefaultFrequency, MIX_DEFAULT_FORMAT, kDefaultChannels, kChunkSize) < 0)
    {
        Logger::error(("SDL_mixer could not initialize! SDL_mixer Error: " + std::string(Mix_GetError())).c_str());
        return false;
    }
    return true;
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

    Mix_CloseAudio();
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
    sounds[id] = sound;
    return true;
}

void SoundManager::playSound(const std::string& id)
{
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
    Mix_PlayMusic(music, -1);
}