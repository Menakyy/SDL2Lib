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

    DropDownList dropdown(Point(100, 100), Size(200, 30), Color(200, 200, 200, 255));
    dropdown.addItem("Option 1");
    dropdown.addItem("Option 2");
    dropdown.addItem("Option 3");

    container.addChild(&dropdown);

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

            dropdown.handleEvents(eventHandler);
        }


        renderer.applyRenderDrawColor();
        renderer.clear();
        container.render();
        renderer.present();
        SDL_Delay(16);
    }

    return 0;
}

// NOLINTEND