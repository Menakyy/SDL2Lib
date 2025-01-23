#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include "Color.h"
#include "View.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class TextField : public View
{
public:
    TextField(const std::string& text, const Point& position, const Size& size, const Color& color, TTF_Font* font);
    ~TextField();

    void render() override;
    void setRenderer(SDL_Renderer* renderer) override;
    void createTexture();

    std::string getText() const;

private:
    SDL_Texture* textTexture = nullptr;
    TTF_Font*    font        = nullptr;
    std::string  text        = "";
    Color        textColor   = { 0, 0, 0, 0 };
    SDL_Rect     textSrcRect = { 0, 0, 0, 0 };
};

#endif  // TEXTFIELD_H