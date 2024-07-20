#include <ranges>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int main()
{
    std::cout << "Enter the list of numbers separated by comma:";
    std::string inputString;
    std::getline(std::cin, inputString);

    constexpr std::string_view delimiter(",");
    auto filteredValues = std::views::split(inputString, delimiter)
        | std::ranges::to<std::vector<std::string>>()
        | std::views::filter([](const auto& str) { try { return std::stod(str) < 0; } catch (const std::exception& e) { return false; } })
        | std::ranges::views::transform([](const auto& str) { return std::stod(str); })
        | std::ranges::to<std::vector<double>>();

    if (filteredValues.empty()) {
        std::cout << "No negative values in the list or incorrect input format\n";
    }
    else {
        std::cout << "Result is " << std::ranges::max(filteredValues) << "\n";
    }
}
