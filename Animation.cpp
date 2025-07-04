#include "Animation.h"

// void Animation::setFramePaths(const std::vector<std::string>& paths)
// {
//     framePaths   = paths;
//     currentFrame = 0;
// }

// void Animation::setFrameTime(int milliseconds)
// {
//     frameTime = milliseconds;
// }

Animation::Animation(const std::vector<std::string>& paths, int milliseconds)
    : framePaths(paths),
      frameTime(milliseconds)
{
}

void Animation::play()
{
    playing       = true;
    lastFrameTime = SDL_GetTicks();
}

void Animation::stop()
{
    playing = false;
}

void Animation::update()
{
    if (!playing || framePaths.empty())
    {
        return;
    }

    Uint32 now = SDL_GetTicks();
    if (now - lastFrameTime >= (Uint32)frameTime)
    {
        currentFrame  = (currentFrame + 1) % framePaths.size();
        lastFrameTime = now;
    }
}

const std::string& Animation::getCurrentFramePath() const
{
    return framePaths[currentFrame];
}
