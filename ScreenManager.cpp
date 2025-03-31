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
    delete activeScreen;
}

void ScreenManager::addScreen(const int id, std::function<std::unique_ptr<Screen>()> screenFactory)
{
    if (!screenFactory)
    {
        Logger::error("Screen factory is nullptr");
        std::abort();
    }

    screenFactories[id] = std::move(screenFactory);
}

Screen* ScreenManager::getActiveScreen() const
{
    return activeScreen;
}

void ScreenManager::setActiveScreen(const int id)
{
    auto it = screenFactories.find(id);
    if (it != screenFactories.end())
    {
        container.clear();
        activeScreen = it->second().release();
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
