#include "Image.h"

#include "Logger.h"

#include <SDL2/SDL_image.h>
#include <iostream>
#include <memory>

Image::Image(const std::string& filePath, const Point& position, const Size& size)
    : View(position, size),
      imageFilePath(filePath)
{
}

Image::~Image()
{
    if (texture != nullptr)
    {
        SDL_DestroyTexture(texture);
    }
}

void Image::tryLoadImage(const std::string& filePath)
{
    SDL_Surface* surfacetmp = IMG_Load(filePath.c_str());
    if (surfacetmp == nullptr)
    {
        Logger::error(("Failed to load image: " + std::string(IMG_GetError())).c_str());
        return;
    }

    texture = SDL_CreateTextureFromSurface(renderer, surfacetmp);

    if (texture == nullptr)
    {
        Logger::error(("Failed to create texture: " + std::string(SDL_GetError())).c_str());
    }
    else
    {
        Logger::error(("Image loaded successfully: " + filePath).c_str());
    }

    ImageSrcRect = { 0, 0, surfacetmp->w, surfacetmp->h };
    SDL_FreeSurface(surfacetmp);
}

void Image::setImageFilePath(const std::string& filePath)
{
    imageFilePath = filePath;
}

std::string Image::getImageFilePath() const
{
    return imageFilePath;
}

void Image::render()
{
    if (texture != nullptr)
    {
        ImageDestRect = { position.getX(), position.getY(), size.getWidth(), size.getHeight() };
        SDL_RenderCopy(renderer, texture, &ImageSrcRect, &ImageDestRect);
    }
}

void Image::setRenderer(SDL_Renderer* renderer)
{
    if (renderer == nullptr)
    {
        Logger::error("Renderer is null");
        return;
    }
    this->renderer = renderer;
}