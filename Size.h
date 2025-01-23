#ifndef SIZE
#define SIZE

class Size
{
public:
    int width, height;

    Size();

    Size(int width, int height);

    ~Size();

    int getWidth() const { return width; }

    int getHeight() const { return height; }
};


#endif /* SIZE */
