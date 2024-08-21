#ifndef POINT
#define POINT

#include <SDL2/SDL.h>
#include <vector>

class Point
{
public:
    Point(SDL_Renderer* renderer, int x, int y);
    Point(SDL_Renderer* renderer, const SDL_Point& point);
    Point(SDL_Renderer* renderer, const std::vector<SDL_Point>& points);
    ~Point();

    void addPoint(const SDL_Point& point);
    void render() const;

private:
    SDL_Renderer*          renderer = nullptr;
    std::vector<SDL_Point> points;
};


#endif /* POINT */
