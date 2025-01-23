#include "TextInput.h"

#include "Logger.h"

TextInput::TextInput(const Point& position, const Size& size, TTF_Font* font, const SDL_Color& color)
    : View(position, size),
      font(font),
      textColor(color)
{
    SDL_StartTextInput();
}

TextInput::~TextInput()
{
    SDL_StopTextInput();
    if (textTexture != nullptr)
    {
        SDL_DestroyTexture(textTexture);
    }
}

void TextInput::handleEvent(const SDL_Event& event)
{
    if (event.type == SDL_TEXTINPUT)
    {
        inputText += event.text.text;
        createTexture();
    }
    else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0)
    {
        inputText.pop_back();
        createTexture();
    }
}

void TextInput::render()
{
    if (textTexture != nullptr)
    {
        SDL_Rect destRect = { position.getX(), position.getY(), size.getWidth(), size.getHeight() };
        SDL_RenderCopy(renderer, textTexture, &textSrcRect, &destRect);
    }
}

std::string TextInput::getText() const
{
    return inputText;
}

void TextInput::clearText()
{
    inputText = "";
    createTexture();
}

void TextInput::createTexture()
{
    if (textTexture != nullptr)
    {
        SDL_DestroyTexture(textTexture);
    }
    if (inputText.empty())
    {
        return;
    }
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, inputText.c_str(), textColor);
    if (textSurface == nullptr)
    {
        Logger::error(("Failed to create text input surface: " + std::string(SDL_GetError())).c_str());
        return;
    }
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (textSurface == nullptr)
    {
        Logger::error(("Failed to create text input texture: " + std::string(SDL_GetError())).c_str());
    }
    else
    {
        textSrcRect = { 0, 0, textSurface->w, textSurface->h };
    }
    SDL_FreeSurface(textSurface);
}

void TextInput::setRenderer(SDL_Renderer* renderer)
{
    if (renderer == nullptr)
    {
        Logger::error("Renderer is null");
        return;
    }
    this->renderer = renderer;
}