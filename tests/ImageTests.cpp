#include "Image.h"
#include "Logger.h"
#include "Renderer.h"
#include "SDLSystem.h"
#include "Window.h"

#include <CppUTest/TestHarness.h>

TEST_GROUP(ImageTest)
{
    SDLSystem* sdlSystem = nullptr;
    Window*    window = nullptr;
    Renderer*  renderer = nullptr;
    Image*     image = nullptr;

    void setup()
    {
        sdlSystem = new SDLSystem(SDL_INIT_VIDEO);
        window    = new Window("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
        renderer  = new Renderer(window->getWindow(), -1, SDL_RENDERER_ACCELERATED);
        image     = new Image("tests/images/Person_3.png", { 220, 205 }, { 70, 200 });
        image->setRenderer(renderer->getRenderer());
    }

    void teardown()
    {
        delete image;
        delete renderer;
        delete window;
        delete sdlSystem;
    }
};

TEST(ImageTest, LoadImage)
{
    image->tryLoadImage("tests/images/Person_3.png");
    CHECK_TRUE(image->getTexture() != nullptr);
}

TEST(ImageTest, RenderImage)
{
    image->tryLoadImage("tests/images/Person_3.png");
    image->render();
}

TEST(ImageTest, SetImageFilePath)
{
    std::string newPath = "tests/images/NewImage.png";
    image->setImageFilePath(newPath);
    STRCMP_EQUAL(newPath.c_str(), image->getImageFilePath().c_str());
}

TEST(ImageTest, ChangePosition)
{
    image->setPosition({ 100, 100 });
    CHECK_EQUAL(100, image->getPosition().getX());
    CHECK_EQUAL(100, image->getPosition().getY());
}

TEST(ImageTest, ChangeSize)
{
    image->setSize({ 200, 200 });
    CHECK_EQUAL(200, image->getSize().getWidth());
    CHECK_EQUAL(200, image->getSize().getHeight());
}
