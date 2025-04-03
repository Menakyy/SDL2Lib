#ifndef SCREENMANAGER
#define SCREENMANAGER


#include "Container.h"
#include "EventHandler.h"
#include "Renderer.h"

#include <SDL2/SDL.h>
#include <functional>
#include <memory>
#include <unordered_map>

class Screen;

class ScreenManager
{
public:
    ScreenManager(Container& container, Renderer& renderer, EventHandler& eventHandler);
    ~ScreenManager();

    void    addScreen(const int id, std::function<std::unique_ptr<Screen>()> screenFactory);
    Screen* getActiveScreen() const;
    void    setActiveScreen(const int id);
    void    update();
    void    render();
    void    handleEvents(bool& exit);

private:
    Container&    container;
    Renderer&     renderer;
    EventHandler& eventHandler;

    std::unordered_map<int, std::function<std::unique_ptr<Screen>()>> screenFactories;
    Screen*                                                           activeScreen;
};


#endif /* SCREENMANAGER */
