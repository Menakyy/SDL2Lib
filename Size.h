#ifndef SIZE
#define SIZE

class Size
{
public:
    Size();

    Size(int width, int height);

    ~Size();

    int getWidth() const { return width; }

    int getHeight() const { return height; }

private:
    int width, height;
};


#endif /* SIZE */
