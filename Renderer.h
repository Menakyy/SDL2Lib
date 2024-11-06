#ifndef RENDERER
#define RENDERER

#include "Color.h"

#include <SDL2/SDL.h>

class Renderer
{
public:
    Renderer(SDL_Window* window, int index, Uint32 flags);
    ~Renderer();

    SDL_Renderer* getRenderer() const;

    void setRenderDrawColor(const Color& color);

    void applyRenderDrawColor();

    void setRenderTarget(SDL_Texture* texture);

    void clear() const;
    void present() const;
    void copy(SDL_Texture* texture, const SDL_Rect* srcrect, const SDL_Rect* dstrect) const;
    void copy(SDL_Texture* texture, const SDL_Rect& srcrect, const SDL_Rect& dstrect) const;

private:
    SDL_Window*   window          = nullptr;
    SDL_Renderer* renderer        = nullptr;
    Color         backgroundColor = { 0, 0, 0, 255 };
};


#endif /* RENDERER */
