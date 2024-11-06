#ifndef LINE_H
#define LINE_H

#include "Point.h"
#include "ShapeView.h"

#include <SDL2/SDL.h>
#include <vector>

class Line : public ShapeView
{
public:
    Line(const Point& startPoint, const Point& endPoint, const Color& color);
    Line(const std::vector<std::pair<Point, Point>>& lines, const Color& color);

    void addLine(const Point& startPoint, const Point& endPoint);
    void render() override;

    void setRenderer(SDL_Renderer* renderer) override;

private:
    std::vector<std::pair<Point, Point>> lines;
};

#endif  // LINE_H