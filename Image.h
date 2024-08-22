#ifndef IMAGE
#define IMAGE

#include <SDL2/SDL.h>
#include <memory>
#include <string>

class Image
{
public:
    Image(SDL_Renderer* renderer, const std::string& filePath);
    ~Image();

    void render(const SDL_Rect* srcRect, const SDL_Rect* destRect) const;
    void render() const;
    void setDestRect(const SDL_Rect& rect);
    void setSrcRect(const SDL_Rect& rect);

    SDL_Rect& getDestRect() { return ImageDestRect; }

    SDL_Rect& getSrcRect() { return ImageSrcRect; }

private:
    SDL_Renderer* renderer = nullptr;
    SDL_Texture*  texture  = nullptr;

    SDL_Rect ImageDestRect = { 0, 0, 0, 0 };
    SDL_Rect ImageSrcRect  = { 0, 0, 0, 0 };

    std::string imageFilePath = "";

    void loadImage(const std::string& filePath);
};

#endif