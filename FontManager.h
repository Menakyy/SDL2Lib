#ifndef FONTMANAGER
#define FONTMANAGER

#include <SDL2/SDL_ttf.h>
#include <memory>
#include <stdexcept>
#include <string>

class FontManager
{
public:
    FontManager(const std::string& fontPath, int fontSize);
    ~FontManager();

    void init();

    TTF_Font* getFont() const { return font; }

private:
    TTF_Font*   font     = nullptr;
    int         fontSize = 0;
    std::string fontPath = "";
};


#endif /* FONTMANAGER */
