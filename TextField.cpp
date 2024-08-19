#include "TextField.h"

#include <iostream>

TextField::TextField(SDL_Renderer*      renderer,
                     const std::string& text,
                     const SDL_Rect&    rect,
                     const SDL_Color&   color,
                     TTF_Font*          font)
    : renderer(renderer),
      text(text),
      textRect(rect),
      textColor(color),
      font(font)
{
    createTextField();
}

TextField::~TextField()
{
    if (textTexture)
    {
        SDL_DestroyTexture(textTexture);
    }
}

void TextField::render() const
{
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
}

void TextField::createTextField()
{
    if (textTexture)
    {
        SDL_DestroyTexture(textTexture);
    }

    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    if (!surface)
    {
        throw std::runtime_error("Failed to create text surface: " + std::string(TTF_GetError()));
    }

    textTexture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!textTexture)
    {
        SDL_FreeSurface(surface);
        throw std::runtime_error("Failed to create text texture: " + std::string(SDL_GetError()));
    }

    SDL_FreeSurface(surface);
}

void TextField::setText(const std::string& newText)
{
    text = newText;
    createTextField();
}

void TextField::setRect(const SDL_Rect& rect)
{
    textRect = rect;
    createTextField();
}

void TextField::setColor(const SDL_Color& color)
{
    textColor = color;
    createTextField();
}
