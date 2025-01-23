#ifndef WINDOW
#define WINDOW


#include <SDL2/SDL.h>
#include <string>

class Window
{
public:
    Window(const std::string& title, int position_x, int position_y, int width, int height, Uint32 flags);
    ~Window();

    SDL_Window* getWindow() const;
    void        setSize(int width, int height);
    void        getSize(int& width, int& height) const;

private:
    SDL_Window*   window   = nullptr;
    SDL_Renderer* renderer = nullptr;

    std::string text   = "";
    int         width  = 0;
    int         height = 0;
};


#endif /* WINDOW */
