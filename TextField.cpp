#include "TextField.h"

#include "Logger.h"
#include "Utilities.h"
#include <stdexcept>

TextField::TextField(const std::string& text,
                     const Point&       position,
                     const Size&        size,
                     const Color&       color,
                     TTF_Font*          font)
    : View(position, size),
      text(text),
      textColor(color),
      font(font)
{
}

TextField::~TextField()
{
    if (textTexture != nullptr)
    {
        SDL_DestroyTexture(textTexture);
    }
}

void TextField::createTexture()
{
    Logger::info(("Creating texture for text: " + text).c_str());

    if (textTexture != nullptr)
    {
        SDL_DestroyTexture(textTexture);
    }

    if (text.empty())
    {
        Logger::error("Text is empty, skipping texture creation.");
        return;
    }

    if (font == nullptr)
    {
        Logger::error("Font is null, cannot create texture.");
        return;
    }

    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), Utilities::convertColorToSDLColor(textColor));
    if (surface == nullptr)
    {
        Logger::error(("Failed to create text surface: " + std::string(TTF_GetError())).c_str());
        return;
    }

    textTexture = SDL_CreateTextureFromSurface(renderer, surface);
    if (textTexture == nullptr)
    {
        Logger::error(("Failed to create text texture: " + std::string(SDL_GetError())).c_str());
    }
    else
    {
        textSrcRect = { 0, 0, surface->w, surface->h };
    }

    SDL_FreeSurface(surface);
}

std::string TextField::getText() const
{
    return text;
}

void TextField::render()
{
    if (textTexture != nullptr)
    {
        SDL_Rect destRect = { position.getX(), position.getY(), size.getWidth(), size.getHeight() };
        SDL_RenderCopy(renderer, textTexture, nullptr, &destRect);
    }
}

void TextField::setRenderer(SDL_Renderer* renderer)
{
    if (renderer == nullptr)
    {
        Logger::error("Renderer is null");
        return;
    }
    this->renderer = renderer;
}