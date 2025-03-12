#include "Rectangle.h"
#include "Renderer.h"
#include "SDLSystem.h"
#include "Window.h"

#include <CppUTest/TestHarness.h>

TEST_GROUP(RectangleTest)
{
    SDLSystem* sdlSystem = nullptr;
    Window*    window    = nullptr;
    Renderer*  renderer  = nullptr;
    Rectangle* rectangle = nullptr;

    void setup()
    {
        sdlSystem = new SDLSystem(SDL_INIT_VIDEO, static_cast<SDLSystem::InitOptions>(SDLSystem::ttf));
        window    = new Window("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
        renderer  = new Renderer(window->getWindow(), -1, SDL_RENDERER_ACCELERATED);
        rectangle = new Rectangle({ 0, 0 }, { 50, 50 }, { 255, 255, 255, 255 }, false);
        rectangle->setRenderer(renderer->getRenderer());
    }

    void teardown()
    {
        delete rectangle;
        delete renderer;
        delete window;
        delete sdlSystem;
    }
};

TEST(RectangleTest, PositionAndSize)
{
    CHECK_EQUAL(0, rectangle->getPosition().getX());
    CHECK_EQUAL(0, rectangle->getPosition().getY());
    CHECK_EQUAL(50, rectangle->getSize().getWidth());
    CHECK_EQUAL(50, rectangle->getSize().getHeight());
}

TEST(RectangleTest, CheckColor)
{
    Color color = rectangle->getColor();
    CHECK_EQUAL(255, color.getR());
    CHECK_EQUAL(255, color.getG());
    CHECK_EQUAL(255, color.getB());
    CHECK_EQUAL(255, color.getA());
}

TEST(RectangleTest, RenderFilled)
{
    rectangle->setFill(true);
    rectangle->render();
    CHECK_TRUE(rectangle->isFill());
}

TEST(RectangleTest, RenderOutline)
{
    rectangle->setFill(false);
    rectangle->render();
    CHECK_FALSE(rectangle->isFill());
}

TEST(RectangleTest, SetRenderer)
{
    SDL_Renderer* newRenderer = renderer->getRenderer();
    rectangle->setRenderer(newRenderer);
    // Add assertions or checks to verify the renderer is set correctly
    CHECK_TRUE(true);
}

TEST(RectangleTest, ChangePosition)
{
    rectangle->setPosition({ 100, 100 });
    CHECK_EQUAL(100, rectangle->getPosition().getX());
    CHECK_EQUAL(100, rectangle->getPosition().getY());
}

TEST(RectangleTest, ChangeSize)
{
    rectangle->setSize({ 200, 200 });
    CHECK_EQUAL(200, rectangle->getSize().getWidth());
    CHECK_EQUAL(200, rectangle->getSize().getHeight());
}