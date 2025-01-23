#ifndef POINT
#define POINT

#include <SDL2/SDL.h>
#include <vector>

class Point
{
public:
    int x, y;

    Point() : x(0), y(0) {}

    Point(int x, int y) : x(x), y(y) {}

    int getX() const { return x; }

    int getY() const { return y; }

    void setX(int x) { this->x = x; }

    void setY(int y) { this->y = y; }
};


#endif /* POINT */
