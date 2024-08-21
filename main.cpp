#include "FontManager.h"
#include "Image.h"
#include "Line.h"
#include "Point.h"
#include "Renderer.h"
#include "SDLSystem.h"
#include "TextField.h"
#include "Window.h"
#include "Rectangle.h"
#include "EventHandler.h"
#include <iostream>
#include <vector>

int pauseTime = 300;

std::string text1 = "Hello, World!";
std::string text2 = "Hello, Planet!";

int main()
{
    SDLSystem sdl(SDL_INIT_VIDEO);
    Window    window("SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    Renderer  renderer(window.getWindow(), -1, SDL_RENDERER_ACCELERATED);
    renderer.setRenderDrawColor(255, 255, 255, 255);

    auto      font = FontManager::loadFont("fonts/LiberationSans-Bold.ttf", 24);
    TextField textField(renderer.getRenderer(), text1, { 0, 0, 200, 50 }, { 0, 0, 0, 255 }, font.get());

    Image image(renderer.getRenderer(), "pngs/Person_2.png");
    SDL_Rect imageSrcRect = { 220, 205, 70, 200 };
    image.setDestRect(imageSrcRect);

    std::vector<SDL_Point> points = { { 50, 100 }, { 100, 150 }, { 150, 200 }, { 200, 250 } };
    Point                  point(renderer.getRenderer(), points);
    point.addPoint({ 250, 300 });

    Line line(renderer.getRenderer(), { 0, 0 }, { 640, 480 });
    line.addLine({ 640, 0 }, { 0, 480 });

    std::vector<std::pair<SDL_Point, SDL_Point>> lines = { { { 50, 0 }, { 50, 480 } }, { { 100, 0 }, { 100, 480 } } };
    Line                                         line2(renderer.getRenderer(), lines);

    SDL_Rect rect1 = { 50, 50, 100, 100 };
    SDL_Rect rect2 = { 200, 50, 100, 100 };
    Rectangle filledRect(renderer.getRenderer(), rect1);
    filledRect.addRect(rect2);
    Rectangle outlinedRect(renderer.getRenderer(), { 350, 50, 100, 100 });

    SDL_Rect rect = { 270, 190, 100, 100 };

    EventHandler eventHandler;

    bool      running = true;
    while (running)
    {
        while (eventHandler.pollEvent())
        {
            if (eventHandler.isQuit())
            {
                running = false;
            }
            else if (eventHandler.isKeyDown())
            {
                switch (eventHandler.getKeyCode())
                {
                    case SDLK_UP:
                        imageSrcRect.y -= 10;  // Przesuń w górę
                        break;
                    case SDLK_DOWN:
                        imageSrcRect.y += 10;  // Przesuń w dół
                        break;
                    case SDLK_LEFT:
                        imageSrcRect.x -= 10;  // Przesuń w lewo
                        break;
                    case SDLK_RIGHT:
                        imageSrcRect.x += 10;  // Przesuń w prawo
                        break;
                }
                image.setDestRect(imageSrcRect);
            }
        }

        renderer.clear();
        image.render();
        renderer.present();
        SDL_Delay(16);
    }

    return 0;
}