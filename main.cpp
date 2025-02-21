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
const int RECTANGLE_SIZE        = 75;

int speed1      = 2;
int speed2      = 2;
int speed3      = 2;
int speed4      = 2;
int textSpeedX1 = 2;
int textSpeedY1 = 2;
int textSpeedX2 = 2;
int textSpeedY2 = 2;

void enterText(Container& container, Renderer& renderer);
void clickToRemoveRectangle(Container& container, Renderer& renderer);
void loopPresentation(Container& container, Renderer& renderer);
void loadImages(Container& container, Renderer& renderer);
void widgetTest(Container& container, Renderer& renderer);
void test(Renderer& renderer);

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

    // enterText(container, renderer);
    // clickToRemoveRectangle(container, renderer);
    // loopPresentation(container, renderer);
    // loadImages(container, renderer);
    // test(renderer);
    widgetTest(container, renderer);

    SDL_Quit();

    return 0;
}

void enterText(Container& container, Renderer& renderer)
{
    auto      font = FontManager::loadFont("fonts/LiberationSans-Bold.ttf", 24);
    TextField promptText("Wpisz: test", { 50, 50 }, { 300, 50 }, { 255, 255, 255, 255 }, font.get());
    TextInput textInput({ 50, 150 }, { 50, 100 }, font.get(), { 255, 255, 255, 255 });

    container.addChild(&promptText);
    container.addChild(&textInput);

    promptText.createTexture();
    textInput.createTexture();

    EventHandler eventHandler;
    bool         waitingForInput = true;

    while (waitingForInput)
    {
        while (eventHandler.pollEvent())
        {
            if (eventHandler.isQuit())
            {
                return;
            }

            if (eventHandler.isTextInput())
            {
                textInput.handleEvent(eventHandler.getEvent());
            }

            if (eventHandler.isKeyDown() && eventHandler.getKeyCode() == SDLK_RETURN)
            {
                if (textInput.getText() == "test")
                {
                    waitingForInput = false;
                }
            }
        }

        renderer.applyRenderDrawColor();
        renderer.clear();
        container.render();
        renderer.present();
        SDL_Delay(16);  // Około 60 FPS
    }
    // Remove the promptText and textInput from the container
    container.clear();
}

void clickToRemoveRectangle(Container& container, Renderer& renderer)
{
    // Add the rectangles for the next screen
    Rectangle redRectangle({ 100, 300 }, { 100, 100 }, { 255, 0, 0, 255 }, true);
    Rectangle blueRectangle({ 600, 300 }, { 100, 100 }, { 0, 0, 255, 255 }, true);
    Rectangle greenRectangle({ DEFAULT_SCREEN_WIDTH / 2, 150 }, { 100, 100 }, { 0, 255, 0, 255 }, true);
    Rectangle yellowRectangle({ DEFAULT_SCREEN_WIDTH / 2, 450 }, { 100, 100 }, { 255, 255, 0, 255 }, true);

    std::vector<Rectangle*> rectangles = { &redRectangle, &blueRectangle, &greenRectangle, &yellowRectangle };

    int  vectorIndex      = 0;
    bool rectangleClicked = false;
    bool waitingForClick  = true;

    EventHandler eventHandler;
    while (waitingForClick)
    {
        while (eventHandler.pollEvent())
        {
            if (eventHandler.isQuit())
            {
                return;
            }

            if (container.getChildrenCount() == 0)
            {
                container.addChild(rectangles[vectorIndex]);
            }

            if (eventHandler.isMouseButtonDown())
            {
                Point mousePos = eventHandler.getMousePosition();
                if (!rectangleClicked && Utilities::isPointInsideRect(mousePos, rectangles[vectorIndex]->getRect()))
                {
                    container.removeChild(rectangles[vectorIndex]);
                    rectangleClicked = true;
                }
                {
                    container.clear();
                    vectorIndex += 1;
                }
            }

            if (vectorIndex == rectangles.size())
            {
                return;
            }
        }

        renderer.applyRenderDrawColor();
        renderer.clear();
        container.render();
        renderer.present();
        SDL_Delay(16);  // Około 60 FPS
    }
}

void loopPresentation(Container& container, Renderer& renderer)
{
    Rectangle rectangle({ 0, 0 }, { RECTANGLE_SIZE, RECTANGLE_SIZE }, { 255, 255, 255, 255 }, false);
    Rectangle rectangle2({ DEFAULT_SCREEN_WIDTH - RECTANGLE_SIZE, 0 },
                         { RECTANGLE_SIZE, RECTANGLE_SIZE },
                         { 0, 0, 255, 255 },
                         false);
    Rectangle rectangle3({ DEFAULT_SCREEN_WIDTH - RECTANGLE_SIZE, DEFAULT_SCREEN_HEIGHT - RECTANGLE_SIZE },
                         { RECTANGLE_SIZE, RECTANGLE_SIZE },
                         { 0, 255, 0, 255 },
                         true);
    Rectangle rectangle4({ 0, DEFAULT_SCREEN_HEIGHT - RECTANGLE_SIZE },
                         { RECTANGLE_SIZE, RECTANGLE_SIZE },
                         { 255, 0, 0, 255 },
                         true);

    Line line(Point(DEFAULT_SCREEN_WIDTH / 2, 0),
              Point(DEFAULT_SCREEN_WIDTH / 2, DEFAULT_SCREEN_WIDTH),
              Color(255, 0, 0, 255));

    Line line2(Point(0, DEFAULT_SCREEN_HEIGHT / 2),
               Point(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT / 2),
               Color(255, 0, 0, 255));

    Image image("pngs/Person_3.png", { 220, 205 }, { 70, 200 });

    auto      font = FontManager::loadFont("fonts/LiberationSans-Bold.ttf", 24);
    TextField textField("Hello World", { 150, 50 }, { 100, 100 }, { 255, 255, 255, 255 }, font.get());
    TextField textField2("Test SDL", { 300, 300 }, { 100, 100 }, { 255, 0, 0, 255 }, font.get());


    // Add other children
    container.addChild(&rectangle);
    container.addChild(&rectangle2);
    container.addChild(&rectangle3);
    container.addChild(&rectangle4);
    container.addChild(&line);
    container.addChild(&line2);
    container.addChild(&image);
    container.addChild(&textField);
    container.addChild(&textField2);

    // Prepare objects
    image.tryLoadImage("pngs/Person_3.png");
    textField.createTexture();
    textField2.createTexture();

    Logger::info("Starting main loop");

    bool      running = true;
    SDL_Event event;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_LEFT:
                        image.setPosition({ image.getPosition().getX() - 10, image.getPosition().getY() });
                        break;
                    case SDLK_RIGHT:
                        image.setPosition({ image.getPosition().getX() + 10, image.getPosition().getY() });
                        break;
                    case SDLK_UP:
                        image.setPosition({ image.getPosition().getX(), image.getPosition().getY() - 10 });
                        break;
                    case SDLK_DOWN:
                        image.setPosition({ image.getPosition().getX(), image.getPosition().getY() + 10 });
                        break;
                }
            }
        }

        // Update rectangle positions
        Point pos1 = rectangle.getPosition();
        pos1.setX(pos1.getX() + speed1);
        if (pos1.getX() + rectangle.getSize().getWidth() >= DEFAULT_SCREEN_WIDTH || pos1.getX() <= 0)
        {
            speed1 = -speed1;
        }
        rectangle.setPosition(pos1);

        // Rectangle 2 moves along the right edge
        Point pos2 = rectangle2.getPosition();
        pos2.setY(pos2.getY() + speed2);
        if (pos2.getY() + rectangle2.getSize().getHeight() >= DEFAULT_SCREEN_HEIGHT || pos2.getY() <= 0)
        {
            speed2 = -speed2;
        }
        rectangle2.setPosition(pos2);

        // Rectangle 3 moves along the bottom edge
        Point pos3 = rectangle3.getPosition();
        pos3.setX(pos3.getX() - speed3);
        if (pos3.getX() + rectangle3.getSize().getWidth() >= DEFAULT_SCREEN_WIDTH || pos3.getX() <= 0)
        {
            speed3 = -speed3;
        }
        rectangle3.setPosition(pos3);

        // Rectangle 4 moves along the left edge
        Point pos4 = rectangle4.getPosition();
        pos4.setY(pos4.getY() - speed4);
        if (pos4.getY() + rectangle4.getSize().getHeight() >= DEFAULT_SCREEN_HEIGHT || pos4.getY() <= 0)
        {
            speed4 = -speed4;
        }
        rectangle4.setPosition(pos4);

        // Update text position
        Point textPos1 = textField.getPosition();
        textPos1.setX(textPos1.getX() + textSpeedX1);
        textPos1.setY(textPos1.getY() + textSpeedY1);

        // Check for boundaries and reverse direction if needed
        if (textPos1.getX() + textField.getSize().getWidth() >= DEFAULT_SCREEN_WIDTH || textPos1.getX() <= 0)
        {
            textSpeedX1 = -textSpeedX1;
        }
        if (textPos1.getY() + textField.getSize().getHeight() >= DEFAULT_SCREEN_HEIGHT || textPos1.getY() <= 0)
        {
            textSpeedY1 = -textSpeedY1;
        }

        textField.setPosition(textPos1);

        // Move the second text field
        Point textPos2 = textField2.getPosition();
        textPos2.setX(textPos2.getX() + textSpeedX2);
        textPos2.setY(textPos2.getY() + textSpeedY2);

        // Check for boundaries and reverse direction if needed
        if (textPos2.getX() + textField2.getSize().getWidth() >= DEFAULT_SCREEN_WIDTH || textPos2.getX() <= 0)
        {
            textSpeedX2 = -textSpeedX2;
        }
        if (textPos2.getY() + textField2.getSize().getHeight() >= DEFAULT_SCREEN_HEIGHT || textPos2.getY() <= 0)
        {
            textSpeedY2 = -textSpeedY2;
        }

        textField2.setPosition(textPos2);

        renderer.applyRenderDrawColor();
        renderer.clear();
        container.render();
        renderer.present();
        SDL_Delay(16);  // Około 60 FPS
    }
}

void loadImages(Container& container, Renderer& renderer)
{
    Image image1("pngs/Mountains.png", { 0, 0 }, { DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT });
    container.addChild(&image1);
    image1.tryLoadImage("pngs/Mountains.png");

    EventHandler eventHandler;
    bool         waitingForClick = true;

    while (waitingForClick)
    {
        while (eventHandler.pollEvent())
        {
            if (eventHandler.isQuit())
            {
                waitingForClick = false;
            }
        }

        renderer.applyRenderDrawColor();
        renderer.clear();
        container.render();
        renderer.present();
        SDL_Delay(16);  // Około 60 FPS
    }
}

void test(Renderer& renderer)
{
    TextField*                textField = nullptr;
    std::shared_ptr<TTF_Font> font;

    font      = FontManager::loadFont("fonts/LiberationSans-Bold.ttf", 24);
    textField = new TextField("Test Text", { 50, 50 }, { 300, 50 }, { 255, 255, 255, 255 }, font.get());
    textField->setRenderer(renderer.getRenderer());
    textField->createTexture();

    EventHandler eventHandler;
    bool         waitingForClick = true;

    while (waitingForClick)
    {
        while (eventHandler.pollEvent())
        {
            if (eventHandler.isQuit())
            {
                waitingForClick = false;
            }
        }

        renderer.applyRenderDrawColor();
        renderer.clear();
        textField->render();  // Render the text field
        renderer.present();
        SDL_Delay(16);  // Około 60 FPS
    }

    delete textField;  // Clean up the text field
}

void widgetTest(Container& container, Renderer& renderer)
{

    auto font = FontManager::loadFont("fonts/LiberationSans-Bold.ttf", 24);

    Button widgetWithColor({ 50, 50 },
                           { 200, 100 },
                           "Hello World",
                           font.get(),
                           { 255, 255, 255, 255 },
                           { 0, 0, 255, 255 });

    container.addChild(&widgetWithColor);

    bool         waitingForClick = true;
    EventHandler eventHandler;

    while (waitingForClick)
    {
        while (eventHandler.pollEvent())
        {
            if (eventHandler.isQuit())
            {
                waitingForClick = false;
            }

            // if (eventHandler.isMouseButtonDown())
            // {
            if (widgetWithColor.isWidgetClicked(eventHandler))
            {
                Logger::info("Button clicked");
            }
            // }


            renderer.applyRenderDrawColor();
            renderer.clear();
            container.render();
            renderer.present();
            SDL_Delay(16);  // Około 60 FPS
        }
    }
    SDL_Quit();
}

// NOLINTEND