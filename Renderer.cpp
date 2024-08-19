#include "Renderer.h"

#include <iostream>

Renderer::Renderer(SDL_Window* window, size_t index, Uint32 flags)
{
    renderer = SDL_CreateRenderer(window, index, flags);

    if (renderer == nullptr)
    {
        throw std::runtime_error("Failed to create renderer: " + std::string(SDL_GetError()));
    }
}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(renderer);
}

SDL_Renderer* Renderer::getRenderer() const
{
    return renderer;
}

void Renderer::setRenderDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
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
