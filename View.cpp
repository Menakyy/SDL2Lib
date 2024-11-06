#include "View.h"

View::View() : position(0, 0), size(0, 0), visible(true), parent(nullptr)
{
}

View::View(const Point& position, const Size& size) : position(position), size(size), visible(true), parent(nullptr)
{
}

View::~View()
{
}