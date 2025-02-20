#ifndef CONTAINER
#define CONTAINER

#include "View.h"

#include <algorithm>
#include <vector>

class Container : public View
{
public:
    Container();

    void addChild(View* view)
    {
        view->setRenderer(this->renderer);
        children.push_back(view);
    }

    void setRenderer(SDL_Renderer* renderer) override
    {
        this->renderer = renderer;
        for (View* child : children)
        {
            child->setRenderer(renderer);
        }
    }

    void render() override
    {
        for (View* child : children)
        {
            child->render();
        }
    }

    void clear() { children.clear(); }

    size_t getChildrenCount() const { return children.size(); }

    void removeChild(View* view)
    {
        auto it = std::find(children.begin(), children.end(), view);
        if (it != children.end())
        {
            children.erase(it);
        }
    }

private:
    std::vector<View*> children{};
    SDL_Renderer*      renderer = nullptr;
};

#endif /* CONTAINER */