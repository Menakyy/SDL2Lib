#ifndef RECTANGLE
#define RECTANGLE

#include "Color.h"
#include "ShapeView.h"

#include <SDL2/SDL.h>
#include <vector>

class Rectangle : public ShapeView
{
public:
    Rectangle(const Point& position, const Size& size, const Color& color, bool fill, int thickness = 1);

    void render() override;

    void setRenderer(SDL_Renderer* renderer) override;

    SDL_Rect getRect() const;

    void setBorderThickness(int thickness);

    int getborderThickness() const;

private:
    void renderFilled() const;
    void renderOutline() const;

private:
    SDL_Renderer* renderer = nullptr;

    int borderThickness = 1;
};


#endif /* RECTANGLE */
