#ifndef UTILITIES
#define UTILITIES

#include "Color.h"
#include "Point.h"
#include "Size.h"

#include <SDL2/SDL.h>

namespace Utilities
{
SDL_Color convertColorToSDLColor(const Color& color);
SDL_Rect  convertToSDLRect(const Point& position, const Size& size);
bool      isPointInsideRect(const Point& point, const SDL_Rect& rect);
Point     getMousePosition(const SDL_Event& event);
}  // namespace Utilities

#endif /* UTILITIES */