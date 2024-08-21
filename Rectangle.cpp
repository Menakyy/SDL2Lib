#include "Rectangle.h"

Rectangle::Rectangle(SDL_Renderer* renderer, const SDL_Rect& rect)
    : renderer(renderer)
{
    rects.push_back(rect);
}

Rectangle::Rectangle(SDL_Renderer* renderer, const std::vector<SDL_Rect>& rects)
    : renderer(renderer), rects(rects)
{
}

Rectangle::~Rectangle()
{
}

void Rectangle::addRect(const SDL_Rect& rect)
{
    rects.push_back(rect);
}

void Rectangle::renderFilled() const
{
    if (!rects.empty())
    {
        SDL_RenderFillRects(renderer, rects.data(), rects.size());
    }
}

void Rectangle::renderOutline() const
{
    if (!rects.empty())
    {
        SDL_RenderDrawRects(renderer, rects.data(), rects.size());
    }
}
