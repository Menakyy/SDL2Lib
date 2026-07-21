#include "SoundManager.h"

#include "Logger.h"

#include <unordered_map>

namespace
{
std::unordered_map<std::string, Mix_Chunk*>& getSharedChunks()
{
    static std::unordered_map<std::string, Mix_Chunk*> sharedChunks;
    return sharedChunks;
}

void haltChunk(Mix_Chunk* chunk)
{
    for (int channel = 0; channel < Mix_AllocateChannels(-1); ++channel)
    {
        if (Mix_GetChunk(channel) == chunk)
        {
            Mix_HaltChannel(channel);
        }
    }
}
}  // namespace

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
        if (sound.second.stopOnCleanup)
        {
            haltChunk(sound.second.chunk);
        }
    }
    sounds.clear();

    if (music != nullptr)
    {
        Mix_HaltMusic();
        Mix_FreeMusic(music);
        music = nullptr;
    }

    // Mix_CloseAudio();
}

bool SoundManager::loadSound(const std::string& id, const std::string& filename, bool stopOnCleanup)
{
    auto&      sharedChunks = getSharedChunks();
    Mix_Chunk* sound        = nullptr;

    auto existing = sharedChunks.find(filename);
    if (existing != sharedChunks.end())
    {
        sound = existing->second;
    }
    else
    {
        sound = Mix_LoadWAV(filename.c_str());
    }

    if (sound == nullptr)
    {
        Logger::error(
            ("Failed to load sound: " + filename + " SDL_mixer Error: " + std::string(Mix_GetError())).c_str());
        return false;
    }

    sharedChunks[filename] = sound;

    Logger::info(("Sound loaded: " + filename).c_str());
    sounds[id] = { sound, stopOnCleanup };
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
    Mix_PlayChannel(-1, it->second.chunk, 0);
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

    const int channelCount = Mix_AllocateChannels(-1);
    for (int ch = 0; ch < channelCount; ++ch)
    {
        if (Mix_GetChunk(ch) == it->second.chunk && Mix_Playing(ch) == 1)
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

    haltChunk(it->second.chunk);
}

bool SoundManager::isMusicPlaying()
{
    return Mix_PlayingMusic() == 1;
}
