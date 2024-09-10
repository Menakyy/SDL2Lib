#ifndef WINDOW
#define WINDOW


#include <SDL2/SDL.h>
#include <string>

class Window
{
public:
    Window(const std::string& title, size_t position_x, size_t position_y, size_t width, size_t height, Uint32 flags);
    ~Window();

    SDL_Window* getWindow() const;
    void setSize(size_t width, size_t height);
    void getSize(size_t& width, size_t& height) const;

private:
    SDL_Window*   window   = nullptr;
    SDL_Renderer* renderer = nullptr;

    std::string text   = "";
    size_t      width  = 0;
    size_t      height = 0;
};


#endif /* WINDOW */
