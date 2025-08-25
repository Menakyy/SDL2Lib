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
const int SLEEP                 = 500;

int main()
{
    Logger::initialize("logs/log.txt", Logger::LogLevel::debug);

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
    frontRect.setSize(Size(0, 30));

    EventHandler eventHandler;
    bool         exit = false;

    float table[]  = { 0.0f, 0.3f, 0.5f, 1.0f, 0.3f };
    float table2[] = { 2.0f, 5.3f, 8.5f, 10.0f, 2.3f };
    float table3[] = { 100.0f, 200.0f, 300.0f, 1000.0f, 100.0f };
    int   idx      = 0;

    statusBar.setFillingType(StatusBar::FillingType::Percent);

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

        statusBar.setProgress(table[idx]);
        SDL_Delay(SLEEP);
        idx = (idx + 1) % 5;
    }


    return 0;
}

// NOLINTEND