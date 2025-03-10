#include "Window.h"
#include "Logger.h"
#include <iostream>

Window::Window(const std::string& title, int position_x, int position_y, int width, int height, Uint32 flags)
{
    window = SDL_CreateWindow(title.c_str(), position_x, position_y, width, height, flags);

    if (window == nullptr)
    {
        Logger::error(("Failed to create window: " + std::string(SDL_GetError())).c_str());
    }
}

Window::~Window()
{
    SDL_DestroyWindow(window);
}

SDL_Window* Window::getWindow() const
{
    return window;
}

void Window::setSize(int width, int height)
{
    SDL_SetWindowSize(window, width, height);
}

void Window::getSize(int& width, int& height) const
{
    int windowW;
    int windowH;
    SDL_GetWindowSize(window, &windowW, &windowH);
    width  = windowW;
    height = windowH;
}
