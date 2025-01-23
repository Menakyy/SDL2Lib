#include "TextField.h"
#include "Logger.h"
#include "Renderer.h"
#include "SDLSystem.h"
#include "Window.h"
#include "FontManager.h"

#include <CppUTest/TestHarness.h>

TEST_GROUP(TextFieldTest)
{
    SDLSystem* sdlSystem = nullptr;
    Window*    window = nullptr;
    Renderer*  renderer = nullptr;
    TextField* textField = nullptr;
    std::shared_ptr<TTF_Font> font;

    void setup()
    {
        sdlSystem = new SDLSystem(SDL_INIT_VIDEO);
        window    = new Window("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
        renderer  = new Renderer(window->getWindow(), -1, SDL_RENDERER_ACCELERATED);
        font      = FontManager::loadFont("tests/fonts/LiberationSans-Bold.ttf", 24);
        textField = new TextField("Test Text", { 50, 50 }, { 300, 50 }, { 255, 255, 255, 255 }, font.get());
        textField->setRenderer(renderer->getRenderer());
        textField->createTexture();
    }

    void teardown()
    {
        delete textField;
        delete renderer;
        delete window;
        delete sdlSystem;
    }
};

TEST(TextFieldTest, CreateTextField)
{
    // textField->createTexture();
    STRCMP_EQUAL("Test Text", textField->getText().c_str());
}

TEST(TextFieldTest, RenderTextField)
{
    // textField->createTexture();
    textField->render();
}

TEST(TextFieldTest, ChangePosition)
{
    textField->setPosition({ 100, 100 });
    CHECK_EQUAL(100, textField->getPosition().getX());
    CHECK_EQUAL(100, textField->getPosition().getY());
}

TEST(TextFieldTest, ChangeSize)
{
    textField->setSize({ 200, 200 });
    CHECK_EQUAL(200, textField->getSize().getWidth());
    CHECK_EQUAL(200, textField->getSize().getHeight());
}