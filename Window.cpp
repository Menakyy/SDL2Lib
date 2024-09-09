#include "Window.h"

#include <iostream>

Window::Window(const std::string& title, size_t position_x, size_t position_y, size_t width, size_t height, Uint32 flags)
{
    window = SDL_CreateWindow(title.c_str(), position_x, position_y, width, height, flags);

    if (window == nullptr)
    {
        throw std::runtime_error("Failed to create window: " + std::string(SDL_GetError()));
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

void Window::setSize(size_t width, size_t height)
{
    SDL_SetWindowSize(window, width, height);
}
