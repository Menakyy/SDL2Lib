#ifndef STATUSBAR
#define STATUSBAR

#include "Color.h"
#include "FontManager.h"
#include "Rectangle.h"
#include "Widget.h"

class StatusBar : public Widget
{
public:
    StatusBar(const Point&       position,
              const Size&        size,
              FontManager*       font,
              const std::string& text            = "",
              const Color&       textColor       = { 255, 255, 255, 255 },
              const Color&       backgroundColor = { 255, 255, 255, 255 },
              const Color&       frontColor      = { 0, 255, 0, 255 });
    ~StatusBar();


    void render() override;
    void handleEvents(EventHandler& eventHandler) override;
    void setRenderer(SDL_Renderer* renderer) override;

    void setText(const std::string& text) { this->text = text; }

    const std::string& getText() const { return text; }

    void setTextColor(const Color& color) { textColor = color; }

    Color getTextColor() const { return textColor; }

    void setBackgroundColor(const Color& color)
    {
        backgroundColor = color;
        backgroundRect.setColor(color);
    }

    Color getBackgroundColor() const { return backgroundColor; }

    void setFrontColor(const Color& color)
    {
        frontColor = color;
        frontRect.setColor(color);
    }

    Color getFrontColor() const { return frontColor; }

    Rectangle& getFrontRectangle() { return frontRect; }

    Rectangle& getBackgroundRectangle() { return backgroundRect; }

    void setProgress(float progress);

private:
    FontManager* font;
    std::string  text;
    Color        textColor;
    Color        backgroundColor;
    Color        frontColor;

    Rectangle backgroundRect;
    Rectangle frontRect;
};


#endif /* STATUSBAR */
