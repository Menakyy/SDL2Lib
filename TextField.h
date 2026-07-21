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
    enum class Alignment
    {
        Left,
        Center,
        Right
    };

    TextField(const std::string& text, const Point& position, const Size& size, const Color& color, TTF_Font* font);
    TextField(const std::string& text,
              const Point&       position,
              const Size&        size,
              const Color&       color,
              const std::string& fontPath,
              int                fontSize);
    ~TextField();

    void render() override;
    void setRenderer(SDL_Renderer* renderer) override;
    void createTexture();

    std::string getText() const;
    void        setTextAndCreateTexture(const std::string& text);
    void        setAlignment(Alignment alignment);
    void        setFontSize(int fontSize);

private:
    Alignment    alignment   = Alignment::Center;
    bool         ownsFont    = false;
    std::string  fontPath    = "";
    int          fontSize    = 0;
    SDL_Texture* textTexture = nullptr;
    TTF_Font*    font        = nullptr;
    std::string  text        = "";
    Color        textColor   = { 0, 0, 0, 0 };
    SDL_Rect     textSrcRect = { 0, 0, 0, 0 };
};

#endif  // TEXTFIELD_H