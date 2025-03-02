#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <SDL2/SDL_mixer.h>
#include <string>
#include <unordered_map>

class SoundManager
{
public:
    static bool init();
    static void cleanup();

    static bool loadSound(const std::string& id, const std::string& filename);
    static void playSound(const std::string& id);
    static void playMusic(const std::string& filename);

private:
    static std::unordered_map<std::string, Mix_Chunk*> sounds;
    static Mix_Music*                                  music;
};

#endif  // SOUNDMANAGER_H