#ifndef SHAPEVIEW
#define SHAPEVIEW
#include "Color.h"
#include "View.h"

class ShapeView : public View
{
public:
    ShapeView(const Point& position, const Size& size, const Color& color, bool fill)
        : View(position, size),
          color(color),
          fill(fill)
    {
    }

    void setFill(bool fill) { this->fill = fill; }

    bool isFill() const { return fill; }

    void setColor(const Color& color) { this->color = color; }

    Color getColor() const { return color; }

protected:
    bool  fill  = false;
    Color color = { 0, 0, 0, 255 };
};


#endif /* SHAPEVIEW */
