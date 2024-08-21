#ifndef LINE
#define LINE

#include <SDL2/SDL.h>
#include <vector>

class Line
{
public:
    Line(SDL_Renderer* renderer, int x1, int y1, int x2, int y2);
    Line(SDL_Renderer* renderer, const SDL_Point& startPoint, const SDL_Point& endPoint);
    Line(SDL_Renderer* renderer, const std::vector<std::pair<SDL_Point, SDL_Point>>& lines);
    ~Line();

    void addLine(const SDL_Point& startPoint, const SDL_Point& endPoint);
    void render() const;
    void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

private:
    SDL_Renderer*                                renderer = nullptr;
    std::vector<std::pair<SDL_Point, SDL_Point>> lines;
};


#endif /* LINE */
