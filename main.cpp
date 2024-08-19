#include "Renderer.h"
#include "SDLSystem.h"
#include "TextField.h"
#include "Window.h"
#include "FontManager.h"
#include "Image.h"
#include <iostream>

int pauseTime = 300;

std::string text1 = "Hello, World!";
std::string text2 = "Hello, Planet!";

// std::shared_ptr
// std::unique_ptr
// std::weak_ptr

int main()
{
    SDLSystem sdl(SDL_INIT_VIDEO);
    Window   window("SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    Renderer renderer(window.getWindow(), -1, SDL_RENDERER_ACCELERATED);
    renderer.setRenderDrawColor(255, 255, 255, 255);

    auto font = FontManager::loadFont("fonts/LiberationSans-Bold.ttf", 24);
    TextField textField(renderer.getRenderer(),
                        text1,
                        { 0, 0, 200, 50 },
                        { 0, 0, 0, 255 },
                        font.get());

    Image image(renderer.getRenderer(), "pngs/Person.png");
    image.setDestRect({ 220, 205, 70, 200 });

    SDL_Event event;
    bool      running = true;
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
            {
                running = false;
            }
        }

        renderer.clear();

        textField.setText(text1);
        textField.setRect({ 0, 0, 200, 50 });
        textField.setColor({ 0, 0, 0, 255 });
        textField.render();

        textField.setText(text2);
        textField.setRect({ 340, 380, 300, 100 });
        textField.setColor({ 100, 100, 100, 255 });
        textField.render();

        image.render();

        renderer.present();
        SDL_Delay(pauseTime);
    }

    return 0;
}