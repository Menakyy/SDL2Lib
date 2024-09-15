#include "CppUTest/TestHarness.h"
#include "Line.h"
#include "SDLSystem.h"

TEST_GROUP(LineTestsGroup)
{
    SDLSystem*    sdlSystem = nullptr;
    SDL_Renderer* renderer  = nullptr;
    Line*         line      = nullptr;

    void setup()
    {
        sdlSystem = new SDLSystem(SDL_INIT_VIDEO);
        SDL_Window* window =
            SDL_CreateWindow("TestWindow", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        line = new Line(renderer, 0, 0, 100, 100);
    }

    void teardown()
    {
        delete line;
        SDL_DestroyRenderer(renderer);
        delete sdlSystem;
    }
};

TEST(LineTestsGroup, LineCreation)
{
    CHECK(line != nullptr);
}

TEST(LineTestsGroup, AddLineTest)
{
    SDL_Point startPoint = { 200, 200 };
    SDL_Point endPoint   = { 300, 300 };

    line->addLine(startPoint, endPoint);

    line->render();
}

TEST(LineTestsGroup, SetColorTest)
{
    Uint8 red = 255, green = 0, blue = 0, alpha = 255;

    line->setColor(red, green, blue, alpha);

    Uint8 r, g, b, a;
    SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);

    CHECK_EQUAL(red, r);
    CHECK_EQUAL(green, g);
    CHECK_EQUAL(blue, b);
    CHECK_EQUAL(alpha, a);
}

TEST(LineTestsGroup, RenderTest)
{
    line->render();
}
