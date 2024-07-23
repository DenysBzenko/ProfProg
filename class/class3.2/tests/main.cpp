#include "../include/UnitTests.hpp"
#include "../src/Triangle.hpp"
#include "../src/Color.hpp"

int main() {
    UnitTests::TestRunner runner;

    runner.runTest("Triangle Area Calculation", [&runner]() {
        Triangle triangle(3, 4, 5);
        double expectedArea = 6.0;
        runner.assertEqual(triangle.area(), expectedArea, "Area of triangle with sides 3, 4, 5 should be 6");
    });

    runner.runTest("Triangle Area Calculation - Equilateral", [&runner]() {
        Triangle triangle(6, 6, 6);
        double expectedArea = std::sqrt(3) * 9;
        runner.assertEqual(triangle.area(), expectedArea, "Area of equilateral triangle with sides 6, 6, 6 should be 6*6*sqrt(3)/4");
    });

    runner.runTest("Triangle Area Calculation - Isosceles", [&runner]() {
        Triangle triangle(5, 5, 8);
        double s = (5 + 5 + 8) / 2;
        double expectedArea = std::sqrt(s * (s - 5) * (s - 5) * (s - 8));
        runner.assertEqual(triangle.area(), expectedArea, "Area of isosceles triangle with sides 5, 5, 8");
    });

    runner.runTest("Color Magic Generation", [&runner]() {
        Color color(100, 50, 200);
        Color magicColor = color.generateMagicColor();
        runner.assertEqual(magicColor.getR(), 49, "R component should be 49");
        runner.assertEqual(magicColor.getG(), 98, "G component should be 98");
        runner.assertEqual(magicColor.getB(), 200, "B component should be 200");
    });

    runner.printResults();
    return runner.getStatus();
}
