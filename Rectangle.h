#ifndef RECTANGLE
#define RECTANGLE

#include <SDL2/SDL.h>
#include <vector>

class Rectangle
{
public:
    Rectangle(SDL_Renderer* renderer, const SDL_Rect& rect);
    Rectangle(SDL_Renderer* renderer, const std::vector<SDL_Rect>& rects);
    ~Rectangle();

    void addRect(const SDL_Rect& rect);
    void renderFilled() const;
    void renderOutline() const;

private:
    SDL_Renderer*         renderer = nullptr;
    std::vector<SDL_Rect> rects;
};


#endif /* RECTANGLE */
