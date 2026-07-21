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

TextField::TextField(const std::string& text,
                     const Point&       position,
                     const Size&        size,
                     const Color&       color,
                     const std::string& fontPath,
                     int                fontSize)
    : View(position, size),
      text(text),
      textColor(color),
      ownsFont(true),
      fontPath(fontPath),
      fontSize(fontSize)
{
    font = TTF_OpenFont(fontPath.c_str(), fontSize);
    if (font == nullptr)
    {
        Logger::error(("Failed to load font: " + fontPath + " " + TTF_GetError()).c_str());
    }
}

TextField::~TextField()
{
    if (textTexture != nullptr)
    {
        SDL_DestroyTexture(textTexture);
    }
    if (ownsFont && font != nullptr)
    {
        TTF_CloseFont(font);
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

void TextField::setTextAndCreateTexture(const std::string& text)
{
    this->text = text;
    createTexture();
}

void TextField::render()
{
    if (not visible)
    {
        return;
    }

    if (textTexture != nullptr)
    {
        int textX = position.getX();
        if (alignment == Alignment::Center)
        {
            textX = position.getX() + (size.getWidth() - textSrcRect.w) / 2;
        }
        else if (alignment == Alignment::Right)
        {
            textX = position.getX() + size.getWidth() - textSrcRect.w;
        }
        int      textY    = position.getY() + (size.getHeight() - textSrcRect.h) / 2;
        SDL_Rect destRect = { textX, textY, textSrcRect.w, textSrcRect.h };
        SDL_RenderCopy(renderer, textTexture, nullptr, &destRect);
    }
}

void TextField::setAlignment(Alignment alignment)
{
    this->alignment = alignment;
}

void TextField::setFontSize(int newFontSize)
{
    if (!ownsFont)
    {
        Logger::error("setFontSize: TextField does not own the font. Use the fontPath constructor.");
        return;
    }
    if (ownsFont && font != nullptr)
    {
        TTF_CloseFont(font);
    }
    fontSize = newFontSize;
    font     = TTF_OpenFont(fontPath.c_str(), fontSize);
    if (font == nullptr)
    {
        Logger::error(("setFontSize: Failed to reload font: " + fontPath + " " + TTF_GetError()).c_str());
        return;
    }
    createTexture();
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