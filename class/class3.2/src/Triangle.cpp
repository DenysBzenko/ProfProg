#include "Triangle.hpp"
#include <cmath>

Triangle::Triangle(double a, double b, double c) : a(a), b(b), c(c) {}

double Triangle::area() const {
    double s = (a + b + c) / 2;
    return std::sqrt(s * (s - a) * (s - b) * (s - c));
}
