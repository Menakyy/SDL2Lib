#include "DropDownList.h"

#include "Logger.h"
#include "Utilities.h"

#include <SDL2/SDL.h>
#include <iostream>

DropDownList::DropDownList(const Point& position, const Size& size, const Color& color)
    : Widget(position, size),
      font("tests/fonts/LiberationSans-Bold.ttf", 24)
{
    dropDownBox =
        new Button(position, size, "DropDownList", font.getFont(), { 255, 255, 255, 255 }, { 0, 0, 255, 255 });
}

DropDownList::~DropDownList()
{
}

void DropDownList::render()
{
    if (renderer)
    {
        dropDownBox->render();

        if (expanded)
        {
            for (size_t i = 0; i < items.size(); ++i)
            {
                TextField itemText(items[i],
                                   Point(position.getX(), position.getY() + (i + 1) * size.getHeight()),
                                   size,
                                   { 255, 255, 255, 255 },
                                   font.getFont());
                itemText.setRenderer(renderer);
                itemText.createTexture();
                itemText.render();
            }
        }
    }
}

void DropDownList::handleEvents(EventHandler& eventHandler)
{
    dropDownBox->handleEvents(eventHandler);

    if (dropDownBox->isClickedNow(eventHandler))
    {
        expanded = !expanded;
        Logger::debug(("DropDownList clicked, expanded: " + std::to_string(expanded)).c_str());
    }

    if (expanded && dropDownBox->isClickedOutside(eventHandler))
    {
        expanded = false;
        Logger::debug("DropDownList collapsed due to outside click.");
    }

    if (expanded)
    {
        Point mousePos = Utilities::getMousePosition(eventHandler.getEvent());

        for (size_t i = 0; i < items.size(); ++i)
        {
            SDL_Rect itemRect =
                Utilities::convertToSDLRect(Point(position.getX(), position.getY() + (i + 1) * size.getHeight()), size);

            if (Utilities::isPointInsideRect(mousePos, itemRect) && eventHandler.isMouseButtonDown())
            {
                selectedIndex = i;
                expanded      = false;  // Zwiń listę po wyborze
                if (onSelectCallback)
                {
                    onSelectCallback(items[i]);
                }
                Logger::info(("Selected item: " + items[i]).c_str());
                break;
            }
        }
    }
}

void DropDownList::setRenderer(SDL_Renderer* renderer)
{
    this->renderer = renderer;
    dropDownBox->setRenderer(renderer);
}

void DropDownList::addItem(const std::string& item)
{
    items.push_back(item);
}

void DropDownList::removeItem(const std::string& item)
{
    items.erase(std::remove(items.begin(), items.end(), item), items.end());
}

void DropDownList::setOnSelectCallback(const std::function<void(const std::string&)>& callback)
{
    onSelectCallback = callback;
}