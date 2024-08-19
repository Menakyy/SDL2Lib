#include "Image.h"

#include <SDL2/SDL_image.h>
#include <iostream>
#include <memory>

Image::Image(SDL_Renderer* renderer, const std::string& filePath) : renderer(renderer)
{
    loadImage(filePath);
}

Image::~Image()
{
    if (texture)
    {
        SDL_DestroyTexture(texture);
    }
}

void Image::loadImage(const std::string& filePath)
{
    SDL_Surface* surfacetmp = IMG_Load(filePath.c_str());
    if (surfacetmp == nullptr)
    {
        std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
        return;
    }

    texture = SDL_CreateTextureFromSurface(renderer, surfacetmp);
    SDL_FreeSurface(surfacetmp);

    if (texture == nullptr)
    {
        std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
    }
    else
    {
        std::cout << "Image loaded successfully: " << filePath << std::endl;
    }
}

void Image::render(const SDL_Rect* srcRect, const SDL_Rect* destRect) const
{
    if (texture != nullptr)
    {
        if(srcRect == nullptr || (srcRect->w == 0 && srcRect->h == 0))
        {
            SDL_RenderCopy(renderer, texture, nullptr, destRect);
        }
        else
        {
            SDL_RenderCopy(renderer, texture, srcRect, destRect);
        }
    }
}

void Image::render() const
{
    render(&ImageSrcRect, &ImageDestRect);
}

void Image::setDestRect(const SDL_Rect& rect)
{
    ImageDestRect = rect;

    std::cout << "Image Dest Rect: x=" << ImageDestRect.x << ", y=" << ImageDestRect.y << ", w=" << ImageDestRect.w
              << ", h=" << ImageDestRect.h << std::endl;
}

void Image::setSrcRect(const SDL_Rect& rect)
{
    ImageSrcRect = rect;
}
