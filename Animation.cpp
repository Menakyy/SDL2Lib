#include "Animation.h"

Animation::Animation(SDL_Texture* texture, int frameWidth, int frameHeight, int numFrames, int frameTime)
    : texture(texture),
      frameWidth(frameWidth),
      frameHeight(frameHeight),
      numFrames(numFrames),
      frameTime(frameTime),
      currentFrame(0),
      elapsedTime(0)
{
}

Animation::~Animation()
{
}

void Animation::update()
{
    elapsedTime += SDL_GetTicks();
    if (elapsedTime >= frameTime)
    {
        currentFrame = (currentFrame + 1) % numFrames;
        elapsedTime  = 0;
    }
}

void Animation::render(SDL_Renderer* renderer, int x, int y)
{
    SDL_Rect srcRect  = { currentFrame * frameWidth, 0, frameWidth, frameHeight };
    SDL_Rect destRect = { x, y, frameWidth, frameHeight };
    SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
}