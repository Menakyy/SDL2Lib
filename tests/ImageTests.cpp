#include "CppUTest/TestHarness.h"
#include "Image.h"
#include "SDLSystem.h"

TEST_GROUP(ImageTestsGroup)
{
    SDLSystem*        sdlSystem        = nullptr;
    SDL_Renderer*     renderer         = nullptr;
    Image*            image            = nullptr;
    const std::string validImagePath   = "tests/images/Rock.png";
    const std::string invalidImagePath = "invalid_image_path.png";

    void setup()
    {
        sdlSystem = new SDLSystem(SDL_INIT_VIDEO);
        SDL_Window* window =
            SDL_CreateWindow("TestWindow", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    }

    void teardown()
    {
        if (image != nullptr)
        {
            delete image;
        }
        SDL_DestroyRenderer(renderer);
        delete sdlSystem;
    }
};

TEST(ImageTestsGroup, ImageCreationSuccess)
{
    image = new Image(renderer, validImagePath);
    CHECK(image != nullptr);
}

TEST(ImageTestsGroup, ImageCreationFailure)
{
    image = new Image(renderer, invalidImagePath);
    CHECK(image != nullptr);
    CHECK(image->getTexture() == nullptr);
}

TEST(ImageTestsGroup, RenderImageTest)
{
    image = new Image(renderer, validImagePath);

    SDL_Rect destRect = { 100, 100, 200, 200 };
    image->setDestRect(destRect);

    image->render();
}

TEST(ImageTestsGroup, SetDestRectTest)
{
    image = new Image(renderer, validImagePath);

    SDL_Rect destRect = { 50, 50, 300, 300 };
    image->setDestRect(destRect);

    SDL_Rect expectedRect = { 50, 50, 300, 300 };
    CHECK_EQUAL(destRect.x, expectedRect.x);
    CHECK_EQUAL(destRect.y, expectedRect.y);
    CHECK_EQUAL(destRect.w, expectedRect.w);
    CHECK_EQUAL(destRect.h, expectedRect.h);
}

TEST(ImageTestsGroup, SetSrcRectTest)
{
    image = new Image(renderer, validImagePath);

    SDL_Rect srcRect = { 10, 10, 100, 100 };
    image->setSrcRect(srcRect);

    SDL_Rect expectedRect = { 10, 10, 100, 100 };
    CHECK_EQUAL(srcRect.x, expectedRect.x);
    CHECK_EQUAL(srcRect.y, expectedRect.y);
    CHECK_EQUAL(srcRect.w, expectedRect.w);
    CHECK_EQUAL(srcRect.h, expectedRect.h);
}
