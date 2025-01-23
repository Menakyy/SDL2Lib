#ifndef VIEW
#define VIEW

#include "Point.h"
#include "Size.h"

#include <vector>

class View
{
public:
    View();

    View(const Point& position, const Size& size);

    virtual ~View();

    virtual void render() = 0;

    virtual void setRenderer(SDL_Renderer* renderer) = 0;

    void setPosition(const Point& position) { this->position = position; }

    Point getPosition() const { return position; }

    Size getSize() const { return size; }

    void setSize(const Size& size) { this->size = size; }

    void setVisible(bool visibility) { visible = visibility; }

    bool isVisible() const { return visible; }

protected:
    Point         position = { 0, 0 };
    Size          size     = { 0, 0 };
    bool          visible  = true;
    bool          fill     = false;
    View*         parent;
    SDL_Renderer* renderer = nullptr;
};

#endif /* VIEW */
