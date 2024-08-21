#include "Line.h"
#include <utility>

Line::Line(SDL_Renderer* renderer, int x1, int y1, int x2, int y2) 
    : renderer(renderer)
{
    lines.push_back({ {x1, y1}, {x2, y2} });
}

Line::Line(SDL_Renderer* renderer, const SDL_Point& startPoint, const SDL_Point& endPoint) 
    : renderer(renderer)
{
    lines.push_back({ startPoint, endPoint });
}

Line::Line(SDL_Renderer* renderer, const std::vector<std::pair<SDL_Point, SDL_Point>>& lines) 
    : renderer(renderer), lines(lines)
{
}

Line::~Line()
{
}

void Line::addLine(const SDL_Point& startPoint, const SDL_Point& endPoint)
{
    lines.push_back({ startPoint, endPoint });
}

void Line::render() const
{
    for (const auto& line : lines)
    {
        SDL_RenderDrawLine(renderer, line.first.x, line.first.y, line.second.x, line.second.y);
    }
}

void Line::setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}
