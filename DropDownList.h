#ifndef DROPDOWNLIST_H
#define DROPDOWNLIST_H

#include "Button.h"
#include "FontManager.h"
#include "Widget.h"

#include <functional>
#include <memory>
#include <string>
#include <vector>

class DropDownList : public Widget
{
public:
    DropDownList(const Point&       position,
                 const Size&        size,
                 const Color&       listColor = { 0, 0, 255, 255 },
                 const Color&       textColor = { 255, 255, 255, 255 },
                 const std::string& title     = "Title");

    ~DropDownList();

    void render() override;
    void handleEvents(EventHandler& eventHandler) override;
    void setRenderer(SDL_Renderer* renderer) override;

    void addItem(const std::string& item);
    void removeItem(const std::string& item);
    void createList();

    void setOnSelectCallback(const std::function<void(const std::string&)>& callback);

    int getSelectedIndex() const;

private:
    std::vector<std::string>             items;
    std::vector<std::unique_ptr<Button>> itemButtons;

    int selectedIndex = -1;

    bool expanded    = false;
    bool expandedTmp = false;

    FontManager                             font;
    std::unique_ptr<Button>                 dropDownBox;
    std::function<void(const std::string&)> onSelectCallback;

    Color listColor = { 0, 0, 0, 255 };
    Color textColor = { 0, 0, 0, 255 };

    void rebuildItemButtons();
};

#endif  // DROPDOWNLIST_H