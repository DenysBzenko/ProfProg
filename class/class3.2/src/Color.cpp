#include "Color.hpp"

Color::Color(int r, int g, int b) : r(r), g(g), b(b) {}

Color Color::generateMagicColor() const {
    int newR = r / 2 - 1;
    int newG = g * 2 - 2;
    int newB = b;
    return Color(newR, newG, newB);
}

int Color::getR() const {
    return r;
}

int Color::getG() const {
    return g;
}

int Color::getB() const {
    return b;
}
