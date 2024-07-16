#include <iostream>
#include <vector>
#include <algorithm>

class Rectangle {
public:
    Rectangle(double width, double height) : width_(width), height_(height), area_(width * height) {}

    double getWidth() const { return width_; }
    double getHeight() const { return height_; }
    double getArea() const { return area_; }

    bool canFitInside(const Rectangle& other) const {
        return width_ <= other.getWidth() && height_ <= other.getHeight();
    }

private:
    double width_;
    double height_;
    double area_;
};

class RectangleProcessor {
public:
    void addRectangle(double width, double height) {
        rectangles_.emplace_back(width, height);
        updateBiggestAndSmallestArea(rectangles_.back().getArea());
    }

    const Rectangle& getBiggestAreaRectangle() const {
        return *std::max_element(rectangles_.begin(), rectangles_.end(), [](const Rectangle& a, const Rectangle& b) {
            return a.getArea() < b.getArea();
        });
    }

    const Rectangle& getSmallestAreaRectangle() const {
        return *std::min_element(rectangles_.begin(), rectangles_.end(), [](const Rectangle& a, const Rectangle& b) {
            return a.getArea() < b.getArea();
        });
    }

    void compareRectangles(size_t index1, size_t index2) const {
        if (index1 < rectangles_.size() && index2 < rectangles_.size()) {
            if (rectangles_[index1].canFitInside(rectangles_[index2])) {
                std::cout << "Rectangle " << index1 + 1 << " can be placed inside Rectangle " << index2 + 1 << std::endl;
            } else {
                std::cout << "Rectangle " << index1 + 1 << " cannot be placed inside Rectangle " << index2 + 1 << std::endl;
            }
        }
    }

private:
    void updateBiggestAndSmallestArea(double area) {
        if (area > biggestArea_) {
            biggestArea_ = area;
        }
        if (area < smallestArea_) {
            smallestArea_ = area;
        }
    }

    std::vector<Rectangle> rectangles_;
    double biggestArea_ = 0;
    double smallestArea_ = 1000000;
};

int main() {
    RectangleProcessor processor;

    for (int i = 0; i < 5; ++i) {
        double width, height;
        std::cout << "Enter rectangle " << i + 1 << ":" << std::endl;
        if (std::cin >> width >> height) {
            processor.addRectangle(width, height);
        }
    }

    for (size_t i = 0; i < 5; ++i) {
        for (size_t j = i + 1; j < 5; ++j) {
            processor.compareRectangles(i, j);
        }
    }

    return 0;
}
