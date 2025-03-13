#include "Utilities.h"

namespace Utilities
{
SDL_Color convertColorToSDLColor(const Color& color)
{
    return { color.getR(), color.getG(), color.getB(), color.getA() };
}

SDL_Rect convertToSDLRect(const Point& position, const Size& size)
{
    SDL_Rect rect;
    rect.x = position.getX();
    rect.y = position.getY();
    rect.w = size.getWidth();
    rect.h = size.getHeight();
    return rect;
}

bool isPointInsideRect(const Point& point, const SDL_Rect& rect)
{
    return point.getX() >= rect.x && point.getX() <= rect.x + rect.w && point.getY() >= rect.y
           && point.getY() <= rect.y + rect.h;
}

Point getMousePosition(const SDL_Event& event)
{
    return Point(event.motion.x, event.motion.y);
}

void wait(int milliseconds)
{
    SDL_Delay(milliseconds);
}

}  // namespace Utilities