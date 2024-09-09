#include "TextInput.h"
#include "Logger.h"

TextInput::TextInput(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color, SDL_Rect rect)
    : renderer(renderer),
      font(font),
      textColor(color),
      textRect(rect),
      inputText("")
{
    SDL_StartTextInput();
    updateTexture();
}

TextInput::~TextInput()
{
    SDL_StopTextInput();
    SDL_DestroyTexture(textTexture);
}

void TextInput::handleEvent(const SDL_Event& event)
{
    if (event.type == SDL_TEXTINPUT)
    {
        inputText += event.text.text;
        updateTexture();
    }
    else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0)
    {
        inputText.pop_back();
        updateTexture();
    }
}

void TextInput::render()
{
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
}

std::string TextInput::getText() const
{
    return inputText;
}

void TextInput::clearText()
{
    inputText = "";
    updateTexture();
}

void TextInput::updateTexture()
{
    if (textTexture != nullptr)
    {
        SDL_DestroyTexture(textTexture);
    }
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, inputText.c_str(), textColor);
    textTexture              = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);

    SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);

    std::string message = "Text: " + inputText;
    Logger::getInstance().log(message);
}