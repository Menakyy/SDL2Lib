#include "Button.h"

#include "Logger.h"
#include "Utilities.h"

Button::Button(const Point&       position,
               const Size&        size,
               const std::string& text,
               TTF_Font*          font,
               const Color&       textColor,
               const Color&       bgColor)
    : Widget(position, size),
      textField(text, position, size, textColor, font),
      backGround(std::make_unique<Rectangle>(position, size, bgColor, true))
{
}

bool Button::isWidgetClicked(EventHandler& eventHandler)
{
    Point    mousePos   = Utilities::getMousePosition(eventHandler.getEvent());
    SDL_Rect widgetRect = Utilities::convertToSDLRect(position, size);

    bool status = eventHandler.isMouseButtonDown() && Utilities::isPointInsideRect(mousePos, widgetRect);

    if (status && clickCallback != nullptr)
    {
        clickCallback->run(this);
    }

    return status;
}

SDL_Rect Button::getRect() const
{
    return Utilities::convertToSDLRect(position, size);
}

void Button::render()
{
    if(not visible)
    {
        return;
    }

    if (backGround != nullptr)
    {
        backGround->render();
    }
    textField.render();
}

void Button::setClickCallback(AbstractCallback* callback)
{
    clickCallback = callback;
}

void Button::setRenderer(SDL_Renderer* renderer)
{
    if (renderer == nullptr)
    {
        Logger::error("Renderer is null");
        return;
    }

    if (backGround == nullptr)
    {
        Logger::error("backGround is null");
        return;
    }

    this->renderer = renderer;
    textField.setRenderer(renderer);
    textField.createTexture();
    backGround->setRenderer(renderer);
}