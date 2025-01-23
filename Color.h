#ifndef COLOR
#define COLOR

#include <SDL2/SDL.h>

class Color
{
public:
    static const Uint8 kAlphaValue = 255;

    Color();
    Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a = kAlphaValue);
    ~Color();

    Uint8 getR() const;
    Uint8 getG() const;
    Uint8 getB() const;
    Uint8 getA() const;

    void setR(Uint8 r);
    void setG(Uint8 g);
    void setB(Uint8 b);
    void setA(Uint8 a);

private:
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
};


#endif /* COLOR */
