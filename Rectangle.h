#ifndef RECTANGLE
#define RECTANGLE

#include "Color.h"
#include "ShapeView.h"

#include <SDL2/SDL.h>
#include <vector>

class Rectangle : public ShapeView
{
public:
    Rectangle(const Point& position, const Size& size, const Color& color, bool fill);

    void render() override;

    void setRenderer(SDL_Renderer* renderer) override;

    SDL_Rect getRect() const;

private:
    void renderFilled() const;
    void renderOutline() const;

private:
    SDL_Renderer* renderer = nullptr;
};


#endif /* RECTANGLE */
