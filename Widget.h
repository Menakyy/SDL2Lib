#ifndef WIDGET
#define WIDGET

#include "Point.h"
#include "Size.h"
#include "View.h"

class Widget : public View
{
public:
    Widget(const Point& position, const Size& size);

private:
};


#endif /* WIDGET */
