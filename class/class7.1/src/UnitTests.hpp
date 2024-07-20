#pragma once

#include <vector>
#include <functional>
#include <string>
#include <iostream>
#include <stdexcept>
#include <source_location>
#include "Rectangle.hpp"
#include "RectangleProcessor.hpp"

#define ASSERT_EQ(leftValue, rightValue) \
    if (leftValue != rightValue) { \
        auto location = std::source_location::current(); \
        std::println("Assert failed: {} (which is equal to {}) is not equal to {} at {}:{}", #leftValue, leftValue, #rightValue, location.file_name(), location.line()); \
        throw std::invalid_argument("Assertion failed"); \
    }

#define ASSERT_NEQ(leftValue, rightValue) \
    if (leftValue == rightValue) { \
        auto location = std::source_location::current(); \
        std::println("Assert failed: {} is equal to {} at {}:{}", #leftValue, #rightValue, location.file_name(), location.line()); \
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
                std::println("Executing test {}...", name);
                totalCount++;
                try {
                    testFunc();
                    std::println("{} {}PASSED{}.", name, greenColor, endColor);
                    successCount++;
                } catch (std::exception& e) {
                    std::println("{} {}FAILED{}.", name, redColor, endColor);
                }
            }
        }
        std::println("{} of {} {} have passed", successCount, totalCount, (totalCount == 1 ? "test" : "tests"));
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
