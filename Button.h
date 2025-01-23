#ifndef BUTTON_H
#define BUTTON_H

#include "AbstractCallback.h"
#include "EventHandler.h"
#include "Image.h"
#include "Rectangle.h"
#include "TextField.h"
#include "Widget.h"

#include <memory>

class Button : public Widget
{
public:
    Button(const Point&       position,
           const Size&        size,
           const std::string& text,
           TTF_Font*          font,
           const Color&       textColor,
           const Color&       bgColor);

    void render() override;
    void setRenderer(SDL_Renderer* renderer) override;

    void setClickCallback(AbstractCallback* callback);

    bool     isWidgetClicked(EventHandler& eventHandler);
    SDL_Rect getRect() const;

private:
    TextField             textField;
    std::unique_ptr<View> backGround;
    AbstractCallback*     clickCallback = nullptr;
};

#endif /* BUTTON_H */