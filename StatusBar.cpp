#include "StatusBar.h"

#include "Logger.h"

StatusBar::StatusBar(const Point&       position,
                     const Size&        size,
                     FontManager*       font,
                     const std::string& text,
                     const Color&       textColor,
                     const Color&       backgroundColor,
                     const Color&       frontColor)
    : Widget(position, size),
      font(font),
      text(text),
      textColor(textColor),
      backgroundColor(backgroundColor),
      frontColor(frontColor),
      backgroundRect(position, size, backgroundColor, true),
      frontRect(position, size, frontColor, true),
      textField(std::make_unique<TextField>(text,
                                            Point(position.getX() + 5, position.getY() + 5),
                                            Size(size.getWidth() - 10, size.getHeight() - 10),
                                            textColor,
                                            font->getFont()))
{
}

StatusBar::~StatusBar()
{
}

void StatusBar::render()
{
    if (renderer == nullptr)
    {
        Logger::error("Renderer is null");
        return;
    }

    backgroundRect.render();
    frontRect.render();
    textField->render();
}

void StatusBar::handleEvents(EventHandler& eventHandler)
{
}

void StatusBar::setRenderer(SDL_Renderer* renderer)
{
    if (renderer == nullptr)
    {
        Logger::error("Renderer is null");
        return;
    }

    this->renderer = renderer;

    backgroundRect.setRenderer(renderer);
    frontRect.setRenderer(renderer);
    textField->setRenderer(renderer);
    textField->createTexture();
}

void StatusBar::setText(const std::string& text)
{
    this->text = text;
    textField->setTextAndCreateTexture(text);
}

void StatusBar::setProgress(float value, int jumps)
{
    float percent = 0.0f;
    switch (fillingType)
    {
        case FillingType::Width:
            percent = value / static_cast<float>(size.getWidth());
            break;
        case FillingType::Percent:
            percent = value;
            break;
        case FillingType::Jump:
            percent = value / static_cast<float>(jumps);
            break;
    }

    if (percent < 0.0f)
    {
        percent = 0.0f;
    }

    if (percent > 1.0f)
    {
        percent = 1.0f;
    }

    int newWidth = static_cast<int>(size.getWidth() * percent);
    frontRect.setSize(Size(newWidth, size.getHeight()));
}