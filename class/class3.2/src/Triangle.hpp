#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

class Triangle {
public:
    Triangle(double a, double b, double c);
    double area() const;

private:
    double a, b, c;
};

#endif 
