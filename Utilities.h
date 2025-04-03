#ifndef UTILITIES
#define UTILITIES

#include "Color.h"
#include "Point.h"
#include "Size.h"

#include <SDL2/SDL.h>

namespace Utilities
{

/**
 * @brief Converts a custom Color object to an SDL_Color object.
 *
 * @param color The custom Color object to convert.
 * @return SDL_Color The equivalent SDL_Color object.
 */
SDL_Color convertColorToSDLColor(const Color& color);

/**
 * @brief Converts a position and size to an SDL_Rect object.
 *
 * @param position The position as a Point object.
 * @param size The size as a Size object.
 * @return SDL_Rect The equivalent SDL_Rect object.
 */
SDL_Rect convertToSDLRect(const Point& position, const Size& size);

/**
 * @brief Checks if a given point is inside a specified SDL_Rect.
 *
 * @param point The point to check.
 * @param rect The SDL_Rect to check against.
 * @return true If the point is inside the rectangle.
 * @return false If the point is outside the rectangle.
 */
bool isPointInsideRect(const Point& point, const SDL_Rect& rect);

/**
 * @brief Retrieves the mouse position from an SDL_Event.
 *
 * @param event The SDL_Event containing mouse data.
 * @return Point The position of the mouse as a Point object.
 */
Point getMousePosition(const SDL_Event& event);

/**
 * @brief Pauses execution for a specified amount of time.
 *
 * @param milliseconds The duration to wait, in milliseconds.
 */
void wait(int milliseconds);

/**
 * @brief Checks if two rectangles, defined by their positions and sizes, intersect.
 *
 * @param point1 The position of the first rectangle as a Point object.
 * @param size1 The size of the first rectangle as a Size object.
 * @param point2 The position of the second rectangle as a Point object.
 * @param size2 The size of the second rectangle as a Size object.
 * @return true If the rectangles intersect.
 * @return false If the rectangles do not intersect.
 */
bool hasIntersection(Point point1, Size size1, Point point2, Size size2);

/**
 * @brief Checks if two SDL_Rect objects intersect.
 *
 * @param rect1 The first SDL_Rect object.
 * @param rect2 The second SDL_Rect object.
 * @return true If the rectangles intersect.
 * @return false If the rectangles do not intersect.
 */
bool hasIntersection(const SDL_Rect& rect1, const SDL_Rect& rect2);
}  // namespace Utilities

#endif /* UTILITIES */