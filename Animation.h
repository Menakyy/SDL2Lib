#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL2/SDL.h>
#include <string>
#include <vector>

class Animation
{
public:
    Animation(const std::vector<std::string>& paths, int milliseconds);
    // void               setFramePaths(const std::vector<std::string>& paths);
    // void               setFrameTime(int milliseconds);
    void               play();
    void               stop();
    void               update();
    const std::string& getCurrentFramePath() const;

private:
    std::vector<std::string> framePaths;
    int                      currentFrame  = 0;
    int                      frameTime     = 100;
    Uint32                   lastFrameTime = 0;
    bool                     playing       = false;
};


#endif  // ANIMATION_H