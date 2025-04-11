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
    DropDownList(const Point& position, const Size& size, const Color& color = Color(255, 255, 255, 255));
    ~DropDownList();

    void render() override;
    void handleEvents(EventHandler& eventHandler) override;
    void setRenderer(SDL_Renderer* renderer) override;

    void addItem(const std::string& item);
    void removeItem(const std::string& item);
    void setOnSelectCallback(const std::function<void(const std::string&)>& callback);

private:
    std::vector<std::string> items;
    size_t                   selectedIndex = 0;

    bool expanded = false;
    bool expandedTmp = false;

    FontManager                             font;
    Button*                                 dropDownBox;
    std::function<void(const std::string&)> onSelectCallback;
};

#endif  // DROPDOWNLIST_H