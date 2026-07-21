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

    bool loadSound(const std::string& id, const std::string& filename, bool stopOnCleanup = true);
    void playSound(const std::string& id);
    void playMusic(const std::string& filename);
    bool isSoundPlaying(const std::string& id);
    void stopSound(const std::string& id);
    bool isMusicPlaying();

private:
    struct Sound
    {
        Mix_Chunk* chunk         = nullptr;
        bool       stopOnCleanup = true;
    };

    std::unordered_map<std::string, Sound> sounds;
    Mix_Music*                             music;
};

#endif  // SOUNDMANAGER_H
