#pragma once

class Rectangle {
public:
    Rectangle(double width, double height);
    double getWidth() const;
    double getHeight() const;
    double getArea() const;
    bool canFitInside(const Rectangle& other) const;

private:
    double width_;
    double height_;
    double area_;
};
