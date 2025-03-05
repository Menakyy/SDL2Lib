#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL2/SDL.h>
#include <vector>

class Animation
{
public:
    Animation(SDL_Texture* texture, int frameWidth, int frameHeight, int numFrames, int frameTime);
    ~Animation();

    void update();
    void render(SDL_Renderer* renderer, int x, int y);

private:
    SDL_Texture* texture;
    int          frameWidth;
    int          frameHeight;
    int          numFrames;
    int          frameTime;
    int          currentFrame;
    int          elapsedTime;
};

#endif  // ANIMATION_H