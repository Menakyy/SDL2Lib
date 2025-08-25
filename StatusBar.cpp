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
      frontRect(position, size, frontColor, true)
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
}

void StatusBar::setProgress(float progress)
{
    if (progress < 0.0f)
    {
        progress = 0.0f;
    }

    if (progress > 1.0f)
    {
        progress = 1.0f;
    }

    int newWidth = static_cast<int>(size.getWidth() * progress);
    frontRect.setSize(Size(newWidth, size.getHeight()));
}
