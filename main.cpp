// NOLINTBEGIN
#include "Button.h"
#include "Container.h"
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

    SDLSystem sdl(SDL_INIT_VIDEO);
    Window    window("SDL2",
                  SDL_WINDOWPOS_CENTERED,
                  SDL_WINDOWPOS_CENTERED,
                  DEFAULT_SCREEN_WIDTH,
                  DEFAULT_SCREEN_HEIGHT,
                  SDL_WINDOW_SHOWN);

    Renderer renderer(window.getWindow(), -1, SDL_RENDERER_ACCELERATED);
    renderer.setRenderDrawColor(Color(0, 0, 0, 255));

    Container container;
    container.setRenderer(renderer.getRenderer());

    FontManager font("fonts/LiberationSans-Bold.ttf", 24);
    TextField   textField("Rock game",
                        { (DEFAULT_SCREEN_WIDTH - DEFAULT_SCREEN_WIDTH / 2) / 2,
                            (DEFAULT_SCREEN_HEIGHT - DEFAULT_SCREEN_HEIGHT / 2) },
                        { DEFAULT_SCREEN_WIDTH / 2, DEFAULT_SCREEN_HEIGHT / 2 },
                        { 255, 255, 255, 255 },
                        font.getFont());

    Button button(
        { (DEFAULT_SCREEN_WIDTH - 200) / 2, (DEFAULT_SCREEN_HEIGHT - 250) / 2 + textField.getSize().getHeight() + 10 },
        { 200, 100 },
        "Start game",
        font.getFont(),
        { 255, 255, 255, 255 },
        { 0, 0, 255, 255 });

    SoundManager::init();
    SoundManager::loadSound("guitar", "sounds/guitar.mp3");

    container.addChild(&textField);

    textField.createTexture();

    EventHandler eventHandler;
    bool         exit = false;
    int value = 250;

    SoundManager::playSound("sounds/guitar.mp3");
    while (not exit)
    {
        if (eventHandler.isQuit() || (value < -250 ))
        {
            exit = true;
        }

        textField.setPosition({ (DEFAULT_SCREEN_WIDTH - DEFAULT_SCREEN_WIDTH / 2) / 2,
                                (DEFAULT_SCREEN_HEIGHT - DEFAULT_SCREEN_HEIGHT / 2) + value});
        value -= 4;

        renderer.applyRenderDrawColor();
        renderer.clear();
        container.render();
        renderer.present();
        SDL_Delay(16);
    }

    exit = false;
    container.addChild(&button);

    while (not exit)
    {
        while (eventHandler.pollEvent())
        {
            if (eventHandler.isQuit())
            {
                exit = true;
            }

            if (button.isWidgetClicked(eventHandler))
            {
                Logger::info("Button clicked");
            }
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