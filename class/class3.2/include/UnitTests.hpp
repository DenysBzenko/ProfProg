#ifndef UNIT_TESTS_HPP
#define UNIT_TESTS_HPP

#include <iostream>
#include <string>
#include <functional>
#include <cmath>

namespace UnitTests {
    class TestRunner {
    public:
        TestRunner() : passed(0), failed(0) {}

        void runTest(const std::string &testName, const std::function<void()> &test) {
            try {
                test();
                passed++;
                std::cout << "[PASS] " << testName << std::endl;
            } catch (const std::exception &e) {
                failed++;
                std::cout << "[FAIL] " << testName << ": " << e.what() << std::endl;
            }
        }

        void assertEqual(double a, double b, const std::string &message) {
            if (std::fabs(a - b) > 1e-6) throw std::runtime_error(message);
        }

        void assertEqual(int a, int b, const std::string &message) {
            if (a != b) throw std::runtime_error(message);
        }

        void printResults() const {
            std::cout << "Passed: " << passed << "\nFailed: " << failed << std::endl;
        }

        int getStatus() const {
            return failed;
        }

    private:
        int passed;
        int failed;
    };
}

#endif 
