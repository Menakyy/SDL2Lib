#ifndef STATUSBAR
#define STATUSBAR

#include "Color.h"
#include "FontManager.h"
#include "Rectangle.h"
#include "TextField.h"
#include "Widget.h"

#include <memory>

class StatusBar : public Widget
{
public:
    enum class FillingType
    {
        Width,
        Percent,
        Jump
    } fillingType = FillingType::Percent;

    StatusBar(const Point&       position,
              const Size&        size,
              FontManager*       font,
              const std::string& text            = "",
              const Color&       textColor       = { 0, 0, 0, 255 },
              const Color&       backgroundColor = { 255, 255, 255, 255 },
              const Color&       frontColor      = { 0, 255, 0, 255 });
    ~StatusBar();


    void render() override;
    void handleEvents(EventHandler& eventHandler) override;
    void setRenderer(SDL_Renderer* renderer) override;

    void setText(const std::string& text);

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

    /*
        statusBar.setProgress(0.5f); - for FillingType::Percent

        statusBar.setProgress(5.0f, 10); - for FillingType::Jump with 10 jumps

        statusBar.setProgress(100.0f); - for FillingType::Width
    */
    void setProgress(float value, int jumps = 10);

    void setFillingType(FillingType type) { fillingType = type; }

    FillingType getFillingType() const { return fillingType; }


private:
    FontManager* font;
    std::string  text;
    Color        textColor;
    Color        backgroundColor;
    Color        frontColor;

    Rectangle backgroundRect;
    Rectangle frontRect;

    std::unique_ptr<TextField> textField = nullptr;
};


#endif /* STATUSBAR */
