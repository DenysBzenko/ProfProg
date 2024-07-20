#pragma once

#include <vector>
#include <functional>
#include <string>
#include <iostream>
#include <stdexcept>
#include <source_location>


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

class RectangleProcessor {
public:
    void addRectangle(double width, double height);
    const Rectangle& getBiggestAreaRectangle() const;
    const Rectangle& getSmallestAreaRectangle() const;
    void compareRectangles(size_t index1, size_t index2) const;

private:
    void updateBiggestAndSmallestArea(double area);
    std::vector<Rectangle> rectangles_;
    double biggestArea_ = 0;
    double smallestArea_ = 1000000;
};

#define ASSERT_EQ(leftValue, rightValue) \
    if ( leftValue != rightValue ) { \
        auto location = std::source_location::current(); \
        std::cerr << "Assert failed: " << #leftValue << " (which is equal to " << leftValue << ") is not equal to " << #rightValue << " at " << location.file_name() << ":" << location.line() << std::endl; \
        throw std::invalid_argument("Assertion failed"); \
    }

#define ASSERT_NEQ(leftValue, rightValue) \
    if ( leftValue == rightValue ) { \
        auto location = std::source_location::current(); \
        std::cerr << "Assert failed: " << #leftValue << " is equal to " << #rightValue << " at " << location.file_name() << ":" << location.line() << std::endl; \
        throw std::invalid_argument("Assertion failed"); \
    }

class UnitTests {
public:
    using TestFunc = std::function<void(void)>;

    void addTest(const std::string& name, TestFunc&& func) {
        tests.push_back({name, std::move(func)});
    }

    void run() {
        constexpr auto greenColor = "\033[32m";
        constexpr auto redColor = "\033[31m";
        constexpr auto endColor = "\033[m";

        size_t totalCount = 0;
        size_t successCount = 0;

        for (auto& [name, testFunc] : tests) {
            if (testFunc) {
                std::cout << "Executing test " << name << "..." << std::endl;
                totalCount++;
                try {
                    testFunc();
                    std::cout << name << " " << greenColor << "PASSED" << endColor << "." << std::endl;
                    successCount++;
                } catch (std::exception& e) {
                    std::cout << name << " " << redColor << "FAILED" << endColor << "." << std::endl;
                }
            }
        }
        std::cout << successCount << " of " << totalCount << " " << (totalCount == 1 ? "test" : "tests") << " have passed" << std::endl;
    }

private:
    std::vector<std::pair<std::string, TestFunc>> tests;
};

void testRectangleArea() {
    Rectangle rect(3.0, 4.0);
    ASSERT_EQ(rect.getArea(), 12.0);
}

void testRectangleFit() {
    Rectangle rect1(3.0, 4.0);
    Rectangle rect2(5.0, 6.0);
    ASSERT_EQ(rect1.canFitInside(rect2), true);
    ASSERT_EQ(rect2.canFitInside(rect1), false);
}

void testRectangleProcessor() {
    RectangleProcessor processor;
    processor.addRectangle(3.0, 4.0);
    processor.addRectangle(5.0, 6.0);

    ASSERT_EQ(processor.getBiggestAreaRectangle().getArea(), 30.0);
    ASSERT_EQ(processor.getSmallestAreaRectangle().getArea(), 12.0);
}

int main() {
    UnitTests tests;
    tests.addTest("testRectangleArea", testRectangleArea);
    tests.addTest("testRectangleFit", testRectangleFit);
    tests.addTest("testRectangleProcessor", testRectangleProcessor);

    tests.run();

    return 0;
}
