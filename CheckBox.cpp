#include "CheckBox.h"

#include "Logger.h"
#include "Utilities.h"

CheckBox::CheckBox(const Point& position, const Size& size, const Color& color)
    : Widget(position, size),
      checkBox(std::make_unique<Rectangle>(position, size, color, false, 3))
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

    if (checkBox == nullptr)
    {
        Logger::error("Checkbox is null");
        return;
    }
    if (checked)
    {
        int   tmpX       = size.getWidth() / 5;
        int   tmpY       = size.getHeight() / 5;
        Point internalPosition = { position.getX() + tmpX, position.getY() + tmpY };
        Size  internalSize     = { size.getWidth() - 2 * tmpX, size.getHeight() - 2 * tmpY };

        Rectangle innerRect(internalPosition, internalSize, Color(0, 255, 0, 255), true);
        innerRect.setRenderer(renderer);
        innerRect.render();
    }
    checkBox->render();
}

void CheckBox::setRenderer(SDL_Renderer* renderer)
{
    if (renderer == nullptr)
    {
        Logger::error("Renderer is null");
        return;
    }

    if (checkBox == nullptr)
    {
        Logger::error("Checkbox is null");
        return;
    }

    this->renderer = renderer;
    checkBox->setRenderer(renderer);
}

void CheckBox::handleEvents(EventHandler& eventHandler)
{
    Point    mousePos   = Utilities::getMousePosition(eventHandler.getEvent());
    SDL_Rect widgetRect = Utilities::convertToSDLRect(position, size);

    hovered = Utilities::isPointInsideRect(mousePos, widgetRect);

    if (eventHandler.isMouseButtonDown() && hovered)
    {
        Logger::info("Checkbox clicked");
        checked = not checked;
    }
}

bool CheckBox::getChecked() const
{
    return checked;
}
