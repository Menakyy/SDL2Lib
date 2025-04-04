#include "Slider.h"

#include "Logger.h"
#include "Utilities.h"

Slider::Slider(const Point& position,
               const Size&  size,
               int          minValue,
               int          maxValue,
               int          initialValue,
               const Color& trackColor,
               const Color& thumbColor)
    : Widget(position, size),
      minValue(minValue),
      maxValue(maxValue),
      currentValue(initialValue),
      track(position, size, trackColor, true),
      thumb({ position.getX(), position.getY() }, { size.getHeight(), size.getHeight() }, thumbColor, true)
{
    updateThumbPosition();
}

void Slider::render()
{
    track.render();

    thumb.render();
}

void Slider::setRenderer(SDL_Renderer* renderer)
{
    if (renderer == nullptr)
    {
        Logger::error("Renderer is null");
        return;
    }

    this->renderer = renderer;

    track.setRenderer(renderer);
    thumb.setRenderer(renderer);
}

void Slider::handleEvents(EventHandler& eventHandler)
{
    Point mousePos = Utilities::getMousePosition(eventHandler.getEvent());

    if (eventHandler.isMouseButtonDown()
        && Utilities::isPointInsideRect(mousePos, Utilities::convertToSDLRect(thumb.getPosition(), thumb.getSize())))
    {
        isDragging = true;
    }

    if (eventHandler.isMouseButtonUp())
    {
        isDragging = false;
    }

    if (isDragging)
    {
        int mouseX   = mousePos.getX();
        currentValue = calculateValueFromPosition(mouseX);
        updateThumbPosition();
    }
}

void Slider::setValue(int value)
{
    currentValue = std::max(minValue, std::min(maxValue, value));
    updateThumbPosition();
}

int Slider::getValue() const
{
    return currentValue;
}

void Slider::updateThumbPosition()
{
    int trackWidth     = track.getSize().getWidth();
    int availableWidth = trackWidth - thumb.getSize().getWidth();
    int offsetX        = ((currentValue - minValue) * availableWidth) / (maxValue - minValue);
    int thumbX         = track.getPosition().getX() + offsetX;

    thumb.setPosition({ thumbX, track.getPosition().getY() });

    Logger::debug(("ThumbX: " + std::to_string(thumbX) + " | currentValue: " + std::to_string(currentValue)
                   + " | minValue: " + std::to_string(minValue) + " | maxValue: " + std::to_string(maxValue))
                      .c_str());
}

int Slider::calculateValueFromPosition(int mouseX)
{
    int trackX     = track.getPosition().getX();
    int trackWidth = track.getSize().getWidth();

    int relativeX = std::max(0, std::min(mouseX - trackX, trackWidth));

    Logger::debug(("RelativeX: " + std::to_string(relativeX)).c_str());

    return minValue + (relativeX * (maxValue - minValue)) / trackWidth;
}