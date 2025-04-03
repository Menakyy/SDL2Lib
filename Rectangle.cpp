#include "Rectangle.h"

#include "Logger.h"
#include "Utilities.h"

Rectangle::Rectangle(const Point& position, const Size& size, const Color& color, bool fill, int thickness)
    : ShapeView(position, size, color, fill),
      borderThickness(thickness)
{
}

void Rectangle::render()
{
    if (not visible)
    {
        return;
    }

    if (fill)
    {
        renderFilled();
    }
    else
    {
        renderOutline();
    }
}

void Rectangle::renderFilled() const
{
    if (renderer != nullptr)
    {
        SDL_SetRenderDrawColor(renderer, color.getR(), color.getG(), color.getB(), color.getA());
        SDL_Rect rect = Utilities::convertToSDLRect(position, size);
        SDL_RenderFillRect(renderer, &rect);
    }
}

void Rectangle::renderOutline() const
{
    if (renderer != nullptr)
    {
        SDL_SetRenderDrawColor(renderer, color.getR(), color.getG(), color.getB(), color.getA());
        SDL_Rect rect = Utilities::convertToSDLRect(position, size);
        if (borderThickness == 1)
        {
            SDL_RenderDrawRect(renderer, &rect);
        }
        else
        {
            for (int i = 0; i < borderThickness; ++i)
            {
                SDL_Rect borderRect = { rect.x - i, rect.y - i, rect.w + 2 * i, rect.h + 2 * i };
                SDL_RenderDrawRect(renderer, &borderRect);
            }
        }
    }
}

SDL_Rect Rectangle::getRect() const
{
    return Utilities::convertToSDLRect(position, size);
}

void Rectangle::setBorderThickness(int thickness)
{
    if (thickness < 0)
    {
        Logger::error("Thickness cannot be negative");
        return;
    }
    borderThickness = thickness;
}

int Rectangle::getborderThickness() const
{
    return borderThickness;
}

void Rectangle::setRenderer(SDL_Renderer* renderer)
{
    if (renderer == nullptr)
    {
        Logger::error("Renderer is null");
        return;
    }
    this->renderer = renderer;
}
