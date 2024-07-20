#include "Rectangle.hpp"

Rectangle::Rectangle(double width, double height) : width_(width), height_(height), area_(width * height) {}

double Rectangle::getWidth() const { return width_; }
double Rectangle::getHeight() const { return height_; }
double Rectangle::getArea() const { return area_; }

bool Rectangle::canFitInside(const Rectangle& other) const {
    return width_ <= other.getWidth() && height_ <= other.getHeight();
}
