#include "CppUTest/TestHarness.h"
#include "SDLSystem.h"
#include "TextField.h"

#include <stdexcept>

TEST_GROUP(TextFieldTestsGroup)
{
    SDLSystem*        sdlSystem   = nullptr;
    SDL_Renderer*     renderer    = nullptr;
    TTF_Font*         font        = nullptr;
    TextField*        textField   = nullptr;
    SDL_Color         white       = { 255, 255, 255, 255 };
    SDL_Rect          rect        = { 100, 100, 200, 50 };
    const std::string initialText = "Hello, World!";

    void setup()
    {
        sdlSystem = new SDLSystem(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
        SDL_Window* window =
            SDL_CreateWindow("TestWindow", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        font = TTF_OpenFont("tests/fonts/LiberationSans-Bold.ttf", 24);
        if (!font) {
            FAIL("Failed to load font");
        }
    }

    void teardown()
    {
        if (textField)
        {
            delete textField;
        }

        if (font)
        {
            TTF_CloseFont(font);
        }

        SDL_DestroyRenderer(renderer);
        TTF_Quit();
        delete sdlSystem;
    }
};

TEST(TextFieldTestsGroup, TextFieldCreation)
{
    textField = new TextField(renderer, initialText, rect, white, font);
    CHECK(textField != nullptr);
}

TEST(TextFieldTestsGroup, RenderTextField)
{
    textField = new TextField(renderer, initialText, rect, white, font);
    textField->render();
}

TEST(TextFieldTestsGroup, SetTextTest)
{
    textField                 = new TextField(renderer, initialText, rect, white, font);
    const std::string newText = "New Text";

    textField->setText(newText);

    CHECK_EQUAL(newText, textField->getText());
}

TEST(TextFieldTestsGroup, SetRectTest)
{
    textField        = new TextField(renderer, initialText, rect, white, font);
    SDL_Rect newRect = { 50, 50, 150, 40 };

    textField->setRect(newRect);

    CHECK_EQUAL(newRect.x, textField->getRect().x);
    CHECK_EQUAL(newRect.y, textField->getRect().y);
    CHECK_EQUAL(newRect.w, textField->getRect().w);
    CHECK_EQUAL(newRect.h, textField->getRect().h);
}

TEST(TextFieldTestsGroup, SetColorTest)
{
    textField          = new TextField(renderer, initialText, rect, white, font);
    SDL_Color newColor = { 0, 0, 255, 255 };

    textField->setColor(newColor);

    CHECK_EQUAL(newColor.r, textField->getColor().r);
    CHECK_EQUAL(newColor.g, textField->getColor().g);
    CHECK_EQUAL(newColor.b, textField->getColor().b);
    CHECK_EQUAL(newColor.a, textField->getColor().a);
}
