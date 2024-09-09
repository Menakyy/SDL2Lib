#ifndef RENDERER
#define RENDERER

#include <SDL2/SDL.h>

class Renderer
{
public:
    Renderer(SDL_Window* window, size_t index, Uint32 flags);
    ~Renderer();

    SDL_Renderer* getRenderer() const;

    void setRenderDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

    void setRenderTarget(SDL_Texture* texture);

    void clear() const;
    void present() const;
    void copy(SDL_Texture* texture, const SDL_Rect* srcrect, const SDL_Rect* dstrect) const;
    void copy(SDL_Texture* texture, const SDL_Rect& srcrect, const SDL_Rect& dstrect) const;

private:
    SDL_Window*   window   = nullptr;
    SDL_Renderer* renderer = nullptr;
};


#endif /* RENDERER */
