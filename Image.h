#ifndef IMAGE
#define IMAGE

#include "View.h"

#include <SDL2/SDL.h>
#include <memory>
#include <string>

class Image : public View
{
public:
    Image(const std::string& filePath, const Point& position, const Size& size);
    ~Image();

    void render() override;
    void setRenderer(SDL_Renderer* renderer) override;

    void        tryLoadImage(/* const std::string& filePath */);
    void        setImageFilePath(const std::string& filePath);
    std::string getImageFilePath() const;

    SDL_Texture* getTexture() const { return texture; }

    void logImageParams();

private:
    SDL_Texture* texture       = nullptr;
    SDL_Rect     ImageDestRect = { 0, 0, 0, 0 };
    SDL_Rect     ImageSrcRect  = { 0, 0, 0, 0 };
    std::string  imageFilePath = "";

    struct ImageParams
    {
        Point position;
        Size  size;
    } imageParams = { { 0, 0 }, { 0, 0 } };
};

#endif  // IMAGE