#include "Line.h"

#include "Logger.h"

Line::Line(const Point& startPoint, const Point& endPoint, const Color& color)
    : ShapeView(startPoint,
                Size(endPoint.getX() - startPoint.getX(), endPoint.getY() - startPoint.getY()),
                color,
                false)
{
    lines.push_back({ startPoint, endPoint });
}

Line::Line(const std::vector<std::pair<Point, Point>>& lines, const Color& color)
    : ShapeView(lines.front().first,
                Size(lines.front().second.getX() - lines.front().first.getX(),
                     lines.front().second.getY() - lines.front().first.getY()),
                color,
                false),
      lines(lines)
{
}

void Line::addLine(const Point& startPoint, const Point& endPoint)
{
    lines.push_back({ startPoint, endPoint });
}

void Line::render()
{
    if (renderer != nullptr)
    {
        SDL_SetRenderDrawColor(renderer, color.getR(), color.getG(), color.getB(), color.getA());
        for (const auto& line : lines)
        {
            SDL_RenderDrawLine(renderer, line.first.getX(), line.first.getY(), line.second.getX(), line.second.getY());
        }
    }
}

void Line::setRenderer(SDL_Renderer* renderer)
{
    if (renderer == nullptr)
    {
        Logger::error("Renderer is null");
        return;
    }
    this->renderer = renderer;
}
