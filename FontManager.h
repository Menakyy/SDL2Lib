#ifndef FONTMANAGER
#define FONTMANAGER

#include <SDL2/SDL_ttf.h>
#include <memory>
#include <stdexcept>
#include <string>

class FontManager
{
public:
    static std::shared_ptr<TTF_Font> loadFont(const std::string& fontPath, int fontSize)
    {
        TTF_Font* font = TTF_OpenFont(fontPath.c_str(), fontSize);
        if (font == nullptr)
        {
            throw std::runtime_error("Failed to load font: " + std::string(TTF_GetError()));
        }
        return std::shared_ptr<TTF_Font>(font, TTF_CloseFont);
    }
};


#endif /* FONTMANAGER */
