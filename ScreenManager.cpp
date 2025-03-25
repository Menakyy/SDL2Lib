#include "ScreenManager.h"

#include "Logger.h"
#include "Screen.h"

ScreenManager::ScreenManager(Container& container, Renderer& renderer, EventHandler& eventHandler)
    : container(container),
      renderer(renderer),
      eventHandler(eventHandler),
      activeScreen(nullptr)
{
}

ScreenManager::~ScreenManager()
{
    container.clear();
}

void ScreenManager::addScreen(const int id, std::unique_ptr<Screen> screen)
{
    if (screen == nullptr)
    {
        Logger::error("Screen is nullptr");
        std::abort();
    }

    screens[id] = std::move(screen);
}

void ScreenManager::setActiveScreen(const int id)
{
    auto it = screens.find(id);
    if (it != screens.end())
    {
        container.clear();
        activeScreen = it->second.get();
        activeScreen->init();
    }
    else
    {
        Logger::error(("Screen not found by id: " + std::to_string(id)).c_str());
        std::abort();
    }
}

void ScreenManager::update()
{
    if (activeScreen != nullptr)
    {
        activeScreen->update();
    }
}

void ScreenManager::render()
{
    if (activeScreen != nullptr)
    {
        activeScreen->render(renderer);
    }
}

void ScreenManager::handleEvents(bool& exit)
{
    if (activeScreen != nullptr)
    {
        activeScreen->handleEvents(eventHandler, exit);
    }
    else
    {
        // Logger::debug("No active screen to handle events");
    }
}
