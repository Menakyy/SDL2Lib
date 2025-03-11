#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <SDL2/SDL_mixer.h>
#include <string>
#include <unordered_map>

class SoundManager
{
public:
    SoundManager();
    ~SoundManager();

    void cleanup();

    bool loadSound(const std::string& id, const std::string& filename);
    void playSound(const std::string& id);
    void playMusic(const std::string& filename);
    bool isSoundPlaying(const std::string& id);
    void stopSound(const std::string& id);
    bool isMusicPlaying();

private:
    std::unordered_map<std::string, Mix_Chunk*> sounds;
    Mix_Music*                                  music;
};

#endif  // SOUNDMANAGER_H