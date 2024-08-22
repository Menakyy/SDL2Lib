#include "EventHandler.h"
#include "FontManager.h"
#include "Image.h"
#include "Line.h"
#include "Point.h"
#include "Rectangle.h"
#include "Renderer.h"
#include "SDLSystem.h"
#include "TextField.h"
#include "Window.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <string>

const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;
const int ROCK_SPEED    = 3;
int points = 0;

void moveRock(Image& rock, int windowWidth, int windowHeight, int rockSpeed, int& points)
{
    SDL_Rect rockSrcRect = rock.getDestRect();

    if (rockSrcRect.y > windowHeight)
    {
        rockSrcRect.y = -10;
        rockSrcRect.x = rand() % (windowWidth - rockSrcRect.w);
        points++;
    }
    rockSrcRect.y += rockSpeed;

    rock.setDestRect(rockSrcRect);
}

bool checkCollision(const SDL_Rect& object1, const SDL_Rect& object2)
{
    return SDL_HasIntersection(&object1, &object2);
}


void presentTextField(Renderer& renderer, TextField& text, int delay)
{
    renderer.clear();
    text.render();
    renderer.present();
    SDL_Delay(delay);
}

int main()
{
    SDLSystem sdl(SDL_INIT_VIDEO);
    Window    window("SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    Renderer  renderer(window.getWindow(), -1, SDL_RENDERER_ACCELERATED);
    renderer.setRenderDrawColor(255, 255, 255, 255);

    Image    person(renderer.getRenderer(), "pngs/Person_3.png");
    SDL_Rect personSrcRect = { 220, 205, 70, 200 };
    person.setDestRect(personSrcRect);

    Image* rock = new Image(renderer.getRenderer(), "pngs/Rock.png");
    SDL_Rect rockSrcRect = { 100, -10, 50, 50 };
    rock->setDestRect(rockSrcRect);

    Image* rock2 = new Image(renderer.getRenderer(), "pngs/Rock.png");
    SDL_Rect rock2SrcRect = { 300, -50, 50, 50 };
    rock2->setDestRect(rock2SrcRect);

    auto font = FontManager::loadFont("fonts/LiberationSans-Bold.ttf", 24);
    std::string pointsText = "points: 0";
    TextField textField(renderer.getRenderer(), pointsText, { SCREEN_WIDTH - 150, 0, 150, 50 }, { 0, 0, 0, 255 }, font.get());

    std::string gameOver = "Game Over!";
    TextField gameOverText(renderer.getRenderer(), gameOver, { SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 50, 200, 100 }, { 255, 0, 0, 255 }, font.get());

    std::string startGame = "Rock Game";
    TextField startGameText(renderer.getRenderer(), startGame, { SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 50, 200, 100 }, { 255, 0, 0, 255 }, font.get());

    std::vector<Image*> images = {rock, rock2};
    EventHandler eventHandler;
    bool         running = true;
    
    presentTextField(renderer, startGameText, 1000);
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
                        personSrcRect.y -= 10;
                        break;
                    case SDLK_DOWN:
                        personSrcRect.y += 10;
                        break;
                    case SDLK_LEFT:
                        personSrcRect.x -= 10;
                        break;
                    case SDLK_RIGHT:
                        personSrcRect.x += 10;
                        break;
                }
                if (personSrcRect.x < 0)
                {
                    personSrcRect.x = 0;
                }
                if (personSrcRect.x > SCREEN_WIDTH - personSrcRect.w)
                {
                    personSrcRect.x = SCREEN_WIDTH - personSrcRect.w;
                }
                if (personSrcRect.y < 0)
                {
                    personSrcRect.y = 0;
                }
                if (personSrcRect.y > SCREEN_HEIGHT - personSrcRect.h)
                {
                    personSrcRect.y = SCREEN_HEIGHT - personSrcRect.h;
                }
                person.setDestRect(personSrcRect);
            }
        }
        
        if (points > 0 && points % 10 == 0 && images.size() < points / 10 + 2)
        {
            Image* newRock = new Image(renderer.getRenderer(), "pngs/Rock.png");
            SDL_Rect newRockSrcRect = { rand() % (SCREEN_WIDTH - 50), -50, 50, 50 };
            newRock->setDestRect(newRockSrcRect);
            images.push_back(newRock);
        }

        for (auto* image : images)
        {
            moveRock(*image, SCREEN_WIDTH, SCREEN_HEIGHT, ROCK_SPEED, points);
        }

        bool collisionDetected = false;
        for (auto& image : images)
        {   
            if (checkCollision(personSrcRect, image->getDestRect()))
            {
                collisionDetected = true;
                break;
            }
        }

        if (collisionDetected)
        {
            std::cout << "Collision detected! Exiting game." << std::endl;
            running = false;
        }

        pointsText = "Points: " + std::to_string(points);
        textField.setText(pointsText);

        renderer.clear();
        person.render();

        for (auto& image : images)
        {
            image->render();
        }

        textField.render();
        renderer.present();
        SDL_Delay(16);
    }

    presentTextField(renderer, gameOverText, 1000);
    
    for (auto* image : images)
    {
        delete image;
    }
    return 0;
}
