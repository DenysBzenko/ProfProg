#pragma once

#include <vector>
#include <functional>
#include <string>
#include <print>
#include <cassert>
#include <source_location>
#include <stdexcept>

#define TEST_CASE(name) \
    static void name(); \
    static bool name##_registered = UnitTests::RegisterTest(#name, name); \
    static void name()

#define ASSERT_EQ(leftValue, rightValue) \
    if ( leftValue != rightValue ) { \
        auto location = std::source_location::current(); \
        std::println("Assert failed: {} (which is equal to {}) is not equal to {} at {}:{}", #leftValue, leftValue, #rightValue, location.file_name(), location.line()); \
        throw std::invalid_argument("Assertion failed"); \
    }

#define ASSERT_NEQ(leftValue, rightValue) \
    if ( leftValue == rightValue ) { \
        auto location = std::source_location::current(); \
        std::println("Assert failed: {} is equal to {} at {}:{}", #leftValue, #rightValue, location.file_name(), location.line()); \
        throw std::invalid_argument("Assertion failed"); \
    }

class UnitTests {
public:
    using TestFunc = std::function<void(void)>;

    static bool RegisterTest(const std::string& name, TestFunc func) {
        GetInstance().tests.push_back({ name, std::move(func) });
        return true;
    }

    static void RunAllTests() {
        auto& instance = GetInstance();
        constexpr auto greenColor = "\033[32m";
        constexpr auto redColor = "\033[31m";
        constexpr auto endColor = "\033[m";

        size_t totalCount = 0;
        size_t successCount = 0;

        for (auto& [name, testFunc] : instance.tests) {
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
        std::println("{} of {} {} have passed", successCount, totalCount, totalCount == 1 ? "test" : "tests");
    }

private:
    UnitTests() = default;

    static UnitTests& GetInstance() {
        static UnitTests instance;
        return instance;
    }

    std::vector<std::pair<std::string, TestFunc>> tests;
};
