#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include "Rectangle.hpp"

class RectangleProcessor {
public:
    void addRectangle(double width, double height) {
        rectangles_.emplace_back(width, height);
        updateBiggestAndSmallestArea(rectangles_.back().getArea());
    }

    const Rectangle& getBiggestAreaRectangle() const {
        if (rectangles_.empty()) {
            throw std::runtime_error("No rectangles available.");
        }
        return *std::max_element(rectangles_.begin(), rectangles_.end(), [](const Rectangle& a, const Rectangle& b) {
            return a.getArea() < b.getArea();
        });
    }

    const Rectangle& getSmallestAreaRectangle() const {
        if (rectangles_.empty()) {
            throw std::runtime_error("No rectangles available.");
        }
        return *std::min_element(rectangles_.begin(), rectangles_.end(), [](const Rectangle& a, const Rectangle& b) {
            return a.getArea() < b.getArea();
        });
    }

    void compareRectangles(size_t index1, size_t index2) const {
        if (index1 < rectangles_.size() && index2 < rectangles_.size()) {
            if (rectangles_[index1].canFitInside(rectangles_[index2])) {
                std::println("Rectangle {} can be placed inside Rectangle {}", index1 + 1, index2 + 1);
            } else {
                std::println("Rectangle {} cannot be placed inside Rectangle {}", index1 + 1, index2 + 1);
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
    double biggestArea_ = std::numeric_limits<double>::lowest();
    double smallestArea_ = std::numeric_limits<double>::max();
};

constexpr size_t NUM_RECTANGLES = 5;

int main() {
    RectangleProcessor processor;

    for (size_t i = 0; i < NUM_RECTANGLES; ++i) {
        double width, height;
        std::println("Enter rectangle {}:", i + 1);
        if (std::cin >> width >> height) {
            processor.addRectangle(width, height);
        }
    }

    for (size_t i = 0; i < NUM_RECTANGLES; ++i) {
        for (size_t j = i + 1; j < NUM_RECTANGLES; ++j) {
            processor.compareRectangles(i, j);
        }
    }

    return 0;
}
