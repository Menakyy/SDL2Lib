#ifndef TEXTINPUT_H
#define TEXTINPUT_H

#include "View.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class TextInput : public View
{
public:
    TextInput(const Point& position, const Size& size, TTF_Font* font, const SDL_Color& color);
    ~TextInput();

    void handleEvent(const SDL_Event& event);
    void render() override;
    void setRenderer(SDL_Renderer* renderer) override;

    std::string getText() const;
    void        clearText();
    void        createTexture();

private:
    SDL_Texture* textTexture  = nullptr;
    TTF_Font*    font         = nullptr;
    std::string  inputText    = "";
    SDL_Color    textColor    = { 0, 0, 0, 0 };
    SDL_Rect     textSrcRect  = { 0, 0, 0, 0 };
    SDL_Rect     textDestRect = { 0, 0, 0, 0 };
};

#endif  // TEXTINPUT_H