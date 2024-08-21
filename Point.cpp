#include "Point.h"

Point::Point(SDL_Renderer* renderer, int x, int y) : renderer(renderer)
{
    points.push_back({ x, y });
}

Point::Point(SDL_Renderer* renderer, const SDL_Point& point) : renderer(renderer)
{
    points.push_back(point);
}


Point::Point(SDL_Renderer* renderer, const std::vector<SDL_Point>& points) : renderer(renderer), points(points)
{
}

Point::~Point()
{
}

void Point::addPoint(const SDL_Point& point)
{
    points.push_back(point);
}

void Point::render() const
{
    for (const auto& point : points)
    {
        SDL_RenderDrawPoint(renderer, point.x, point.y);
    }
}
