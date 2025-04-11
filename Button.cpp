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

void Button::handleEvents(EventHandler& eventHandler)
{
    Point    mousePos   = Utilities::getMousePosition(eventHandler.getEvent());
    SDL_Rect widgetRect = Utilities::convertToSDLRect(position, size);

    hovered = Utilities::isPointInsideRect(mousePos, widgetRect);

    if (eventHandler.isMouseButtonDown() && hovered)
    {
        if (clickCallback != nullptr)
        {
            clickCallback->run(this);
        }
        isClicked = true;
    }
}

SDL_Rect Button::getRect() const
{
    return Utilities::convertToSDLRect(position, size);
}

bool Button::isClickedNow(const EventHandler& eventHandler) const
{
    if (eventHandler.isMouseButtonDown())
    {
        Point    mousePos   = Utilities::getMousePosition(eventHandler.getEvent());
        SDL_Rect widgetRect = Utilities::convertToSDLRect(position, size);
        return Utilities::isPointInsideRect(mousePos, widgetRect);
    }
    return false;
}

bool Button::isClickedOutside(const EventHandler& eventHandler) const
{
    if (eventHandler.isMouseButtonDown())
    {
        Point    mousePos   = Utilities::getMousePosition(eventHandler.getEvent());
        SDL_Rect widgetRect = Utilities::convertToSDLRect(position, size);
        return !Utilities::isPointInsideRect(mousePos, widgetRect);
    }
    return false;
}

void Button::render()
{
    if (!visible)
    {
        return;
    }

    SDL_Rect widgetRect = Utilities::convertToSDLRect(position, size);

    if (backGround != nullptr)
    {
        backGround->render();
    }

    if (hovered)
    {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

        for (int i = 0; i < kBorderThickness; ++i)
        {
            SDL_Rect borderRect = { widgetRect.x - i, widgetRect.y - i, widgetRect.w + 2 * i, widgetRect.h + 2 * i };
            SDL_RenderDrawRect(renderer, &borderRect);
        }
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