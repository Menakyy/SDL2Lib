#ifndef TEXTFIELD
#define TEXTFIELD

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class TextField
{
public:
    TextField(SDL_Renderer*      renderer,
              const std::string& text,
              const SDL_Rect&    rect,
              const SDL_Color&   color,
              TTF_Font*          font);
    ~TextField();

    void render() const;
    void setText(const std::string& newText);

    void setRect(const SDL_Rect& rect);
    void setColor(const SDL_Color& color);

    const SDL_Rect& getRect() const { return textRect; }
    const SDL_Color& getColor() const { return textColor; }
    const std::string& getText() const { return text; }

private:
    void createTextField();

private:
    SDL_Renderer* renderer    = nullptr;
    SDL_Texture*  textTexture = nullptr;
    TTF_Font*     font        = nullptr;

    std::string text      = "";
    SDL_Color   textColor = { 0, 0, 0, 0 };
    SDL_Rect    textRect  = { 0, 0, 0, 0 };
};


#endif /* TEXTFIELD */
