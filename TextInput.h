#ifndef TEXTINPUT
#define TEXTINPUT

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class TextInput
{
public:
    TextInput(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color, SDL_Rect rect);

    ~TextInput();

    void handleEvent(const SDL_Event& event);

    void render();

    std::string getText() const;

    void clearText();

private:
    SDL_Renderer* renderer    = nullptr;
    TTF_Font*     font        = nullptr;
    SDL_Color     textColor   = { 0, 0, 0, 0 };
    SDL_Rect      textRect    = { 0, 0, 0, 0 };
    SDL_Texture*  textTexture = nullptr;
    std::string   inputText   = "";

    void updateTexture();
};

#endif /* TEXTINPUT */