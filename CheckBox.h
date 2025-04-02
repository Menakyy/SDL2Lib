#ifndef CHECKBOX
#define CHECKBOX

#include "Rectangle.h"
#include "Widget.h"

#include <SDL2/SDL.h>
#include <string>

class CheckBox : public Widget
{
public:
    CheckBox(const Point& position, const Size& size, const Color& color = Color(255, 255, 255, 255));
    ~CheckBox();

    void render() override;
    void setRenderer(SDL_Renderer* renderer) override;

    void handleEvents(EventHandler& eventHandler) override;

private:
    Rectangle* checkBox = nullptr;
};


#endif /* CHECKBOX */
