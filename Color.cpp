#include "Color.h"

Color::Color() : r(0), g(0), b(0), a(kAlphaValue)
{
}

Color::Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a) : r(r), g(g), b(b), a(a)
{
}

Color::~Color()
{
}

Uint8 Color::getR() const
{
    return r;
}

Uint8 Color::getG() const
{
    return g;
}

Uint8 Color::getB() const
{
    return b;
}

Uint8 Color::getA() const
{
    return a;
}

void Color::setR(Uint8 r)
{
    this->r = r;
}

void Color::setG(Uint8 g)
{
    this->g = g;
}

void Color::setB(Uint8 b)
{
    this->b = b;
}

void Color::setA(Uint8 a)
{
    this->a = a;
}