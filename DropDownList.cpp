#include "DropDownList.h"

#include "Button.h"
#include "Logger.h"
#include "Utilities.h"

#include <SDL2/SDL.h>
#include <iostream>

DropDownList::DropDownList(const Point&       position,
                           const Size&        size,
                           const Color&       listColor,
                           const Color&       textColor,
                           const std::string& title)
    : Widget(position, size),
      listColor(listColor),
      textColor(textColor),
      font("assets/fonts/LiberationSans-Bold.ttf", 24),
      dropDownBox(std::make_unique<Button>(position, size, title, font.getFont(), textColor, listColor))
{
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
            for (const auto& button : itemButtons)
            {
                button->render();
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

    if (expanded)
    {
        for (size_t i = 0; i < itemButtons.size(); ++i)
        {
            itemButtons[i]->handleEvents(eventHandler);

            if (itemButtons[i]->isClickedNow(eventHandler))
            {
                selectedIndex = i;
                expanded      = false;

                if (onSelectCallback)
                {
                    onSelectCallback(items[i]);
                }

                Logger::info(("Selected item: " + items[i]).c_str());
                break;
            }
        }
    }

    if (expanded && dropDownBox->isClickedOutside(eventHandler))
    {
        expanded = false;
        Logger::debug("DropDownList collapsed due to outside click.");
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
    rebuildItemButtons();
}

void DropDownList::createList()
{
    if (items.empty())
    {
        Logger::error("No items to create in the dropdown list.");
        return;
    }
    rebuildItemButtons();
}

void DropDownList::setOnSelectCallback(const std::function<void(const std::string&)>& callback)
{
    onSelectCallback = callback;
}

int DropDownList::getSelectedIndex() const
{
    return selectedIndex;
}

void DropDownList::rebuildItemButtons()
{
    itemButtons.clear();

    for (size_t i = 0; i < items.size(); ++i)
    {
        const int spacing = 5;
        Point     itemPos(position.getX(), position.getY() + (i + 1) * size.getHeight() + spacing * i);

        auto button = std::make_unique<Button>(itemPos, size, items[i], font.getFont(), textColor, listColor);

        // Logger::debug(("Text color: " + std::to_string(textColor.getR()) + ", " + std::to_string(textColor.getG())
        //                + ", " + std::to_string(textColor.getB()) + ", " + std::to_string(textColor.getA()))
        //                   .c_str());
        // Logger::debug(("Background color: " + std::to_string(listColor.getR()) + ", " +
        // std::to_string(listColor.getG())
        //                + ", " + std::to_string(listColor.getB()) + ", " + std::to_string(listColor.getA()))
        //                   .c_str());

        button->setRenderer(renderer);
        itemButtons.push_back(std::move(button));
    }
}
