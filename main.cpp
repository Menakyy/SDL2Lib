// NOLINTBEGIN
#include "Button.h"
#include "Container.h"
#include "DropDownList.h"
#include "EventHandler.h"
#include "FontManager.h"
#include "Image.h"
#include "Line.h"
#include "Logger.h"
#include "Point.h"
#include "Rectangle.h"
#include "Renderer.h"
#include "SDLSystem.h"
#include "SoundManager.h"
#include "StatusBar.h"
#include "TextField.h"
#include "TextInput.h"
#include "Utilities.h"
#include "Window.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>


const int DEFAULT_SCREEN_WIDTH  = 840;
const int DEFAULT_SCREEN_HEIGHT = 680;

int main()
{
    Logger::initialize("logs/log.txt", Logger::LogLevel::info);

    SDLSystem sdl(SDL_INIT_VIDEO, static_cast<SDLSystem::InitOptions>(SDLSystem::ttf | SDLSystem::audio));

    Window window("SDL2",
                  SDL_WINDOWPOS_CENTERED,
                  SDL_WINDOWPOS_CENTERED,
                  DEFAULT_SCREEN_WIDTH,
                  DEFAULT_SCREEN_HEIGHT,
                  SDL_WINDOW_SHOWN);

    Renderer renderer(window.getWindow(), -1, SDL_RENDERER_ACCELERATED);
    renderer.setRenderDrawColor(Color(0, 0, 0, 255));

    Container container;
    container.setRenderer(renderer.getRenderer());

    FontManager fontManager("assets/fonts/LiberationSans-Bold.ttf", 24);

    // TextInput textInput(Point(100, 200), Size(200, 30), fontManager.getFont(), { 255, 0, 0, 255 });
    // container.addChild(&textInput);

    StatusBar statusBar(Point(100, 200), Size(400, 30), &fontManager, "Status Bar");
    container.addChild(&statusBar);

    auto& frontRect = statusBar.getFrontRectangle();
    frontRect.setSize(Size(50, 30));

    EventHandler eventHandler;
    bool         exit = false;

    while (not exit)
    {
        while (eventHandler.pollEvent())
        {
            if (eventHandler.isQuit())
            {
                exit = true;
            }

            // textInput.handleEvent(eventHandler.getEvent());
        }

        renderer.applyRenderDrawColor();
        renderer.clear();
        container.render();
        renderer.present();
        SDL_Delay(16);

        frontRect.setSize(Size(frontRect.getSize().getWidth() + 1, 30));
    }

    return 0;
}

// NOLINTEND