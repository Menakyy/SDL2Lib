#include "CheckBox.h"

#include "Logger.h"

CheckBox::CheckBox(const Point& position, const Size& size, const Color& color) : Widget(position, size)
{
}

CheckBox::~CheckBox()
{
}

void CheckBox::render()
{
    if (not visible)
    {
        return;
    }
}

void CheckBox::setRenderer(SDL_Renderer* renderer)
{
    if (renderer == nullptr)
    {
        Logger::error("Renderer is null");
        return;
    }
    this->renderer = renderer;
}

void CheckBox::handleEvents(EventHandler& eventHandler)
{
    if (eventHandler.isMouseButtonDown())
    {
        Point mousePos = eventHandler.getMousePosition();
    }
}
