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
    static constexpr int kBorderThickness = 3;

    Button(const Point&       position,
           const Size&        size,
           const std::string& text,
           TTF_Font*          font,
           const Color&       textColor,
           const Color&       bgColor);

    void render() override;
    void setRenderer(SDL_Renderer* renderer) override;

    void setClickCallback(AbstractCallback* callback);

    void     handleEvents(EventHandler& eventHandler) override;
    SDL_Rect getRect() const;

    bool getClicked() const { return isClicked; }

    bool isClickedNow(const EventHandler& eventHandler) const;
    bool isClickedOutside(const EventHandler& eventHandler) const;

    void setEnabled(bool active);

private:
    TextField             textField;
    std::unique_ptr<View> backGround;
    AbstractCallback*     clickCallback = nullptr;

    bool hovered   = false;
    bool isClicked = false;
    bool isActive  = true;
};

#endif /* BUTTON_H */