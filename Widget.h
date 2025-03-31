#ifndef WIDGET
#define WIDGET

#include "EventHandler.h"
#include "Point.h"
#include "Size.h"
#include "View.h"

class Widget : public View
{
public:
    Widget(const Point& position, const Size& size);

    virtual void handleEvents(EventHandler& eventHandler) = 0;

private:
};


#endif /* WIDGET */
