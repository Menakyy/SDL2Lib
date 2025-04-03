#ifndef SLIDER_H
#define SLIDER_H

#include "Color.h"
#include "EventHandler.h"
#include "Rectangle.h"
#include "Widget.h"

class Slider : public Widget
{
public:
    Slider(const Point& position,
           const Size&  size,
           int          minValue,
           int          maxValue,
           int          initialValue,
           const Color& trackColor = { 255, 255, 255, 255 },
           const Color& thumbColor = { 0, 0, 255, 255 });

    void render() override;
    void setRenderer(SDL_Renderer* renderer) override;
    void handleEvents(EventHandler& eventHandler) override;

    void setValue(int value);
    int  getValue() const;

private:
    int minValue;
    int maxValue;
    int currentValue;

    Rectangle track;
    Rectangle thumb;

    bool isDragging = false;

    void updateThumbPosition();
    int  calculateValueFromPosition(int mouseX);
};

#endif  // SLIDER_H