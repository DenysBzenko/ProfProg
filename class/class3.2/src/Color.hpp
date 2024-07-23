#ifndef COLOR_HPP
#define COLOR_HPP

class Color {
public:
    Color(int r, int g, int b);
    Color generateMagicColor() const;

    int getR() const;
    int getG() const;
    int getB() const;

private:
    int r, g, b;
};

#endif 
