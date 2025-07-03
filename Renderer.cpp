#include "Renderer.h"

#include <iostream>

Renderer::Renderer(SDL_Window* window, int index, Uint32 flags)
{
    renderer = SDL_CreateRenderer(window, index, flags);

    if (renderer == nullptr)
    {
        throw std::runtime_error("Failed to create renderer: " + std::string(SDL_GetError()));
    }
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(renderer);
}

SDL_Renderer* Renderer::getRenderer() const
{
    return renderer;
}

void Renderer::setRenderDrawColor(const Color& color)
{
    backgroundColor = color;
    SDL_SetRenderDrawColor(renderer, color.getR(), color.getG(), color.getB(), color.getA());
}

void Renderer::applyRenderDrawColor()
{
    SDL_SetRenderDrawColor(renderer,
                           backgroundColor.getR(),
                           backgroundColor.getG(),
                           backgroundColor.getB(),
                           backgroundColor.getA());
}

void Renderer::setRenderTarget(SDL_Texture* texture)
{
    SDL_SetRenderTarget(renderer, texture);
}

void Renderer::clear() const
{
    SDL_RenderClear(renderer);
}

void Renderer::present() const
{
    SDL_RenderPresent(renderer);
}

void Renderer::copy(SDL_Texture* texture, const SDL_Rect& srcrect, const SDL_Rect& dstrect) const
{
    SDL_RenderCopy(renderer, texture, &srcrect, &dstrect);
}

void Renderer::copy(SDL_Texture* texture, const SDL_Rect* srcrect, const SDL_Rect* dstrect) const
{
    SDL_RenderCopy(renderer, texture, srcrect, dstrect);
}
