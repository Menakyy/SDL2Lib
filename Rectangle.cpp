#include "Rectangle.h"

#include "Logger.h"
#include "Utilities.h"

Rectangle::Rectangle(const Point& position, const Size& size, const Color& color, bool fill)
    : ShapeView(position, size, color, fill)
{
}

void Rectangle::render()
{
    if(not visible)
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
        // Logger::getInstance().log("Rendering filled rectangle at position: " + std::to_string(position.getX()) + ", "
        //                           + std::to_string(position.getY()) + " with size: " +
        //                           std::to_string(size.getWidth())
        //                           + ", " + std::to_string(size.getHeight()));
        SDL_RenderFillRect(renderer, &rect);
    }
}

void Rectangle::renderOutline() const
{
    if (renderer != nullptr)
    {
        SDL_SetRenderDrawColor(renderer, color.getR(), color.getG(), color.getB(), color.getA());
        SDL_Rect rect = Utilities::convertToSDLRect(position, size);
        // Logger::getInstance().log("Rendering outline rectangle at position: " + std::to_string(position.getX()) + ",
        // "
        //                           + std::to_string(position.getY()) + " with size: " +
        //                           std::to_string(size.getWidth())
        //                           + ", " + std::to_string(size.getHeight()));
        SDL_RenderDrawRect(renderer, &rect);
    }
}

SDL_Rect Rectangle::getRect() const
{
    return Utilities::convertToSDLRect(position, size);
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
