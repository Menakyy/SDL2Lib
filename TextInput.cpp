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
    else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE && not inputText.empty())
    {
        inputText.pop_back();
        createTexture();
    }
}

void TextInput::render()
{
    if (not visible)
    {
        return;
    }

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
        textTexture = nullptr;
    }

    if (renderer == nullptr)
    {
        Logger::error("TextInput: renderer is null in createTexture()");
        return;
    }

    if (inputText.empty())
    {
        textSrcRect = { 0, 0, 0, 0 };
        return;
    }

    SDL_Surface* textSurface = TTF_RenderUTF8_Blended(font, inputText.c_str(), textColor);
    if (!textSurface)
    {
        Logger::error(("Failed to create text surface: " + std::string(TTF_GetError())).c_str());
        return;
    }

    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!textTexture)
    {
        Logger::error(("Failed to create text texture: " + std::string(SDL_GetError())).c_str());
        SDL_FreeSurface(textSurface);
        return;
    }

    textSrcRect = { 0, 0, textSurface->w, textSurface->h };
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