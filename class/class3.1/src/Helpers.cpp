#include "Helpers.hpp"
#include <algorithm> 

double dummyFunc(double x) {
    return x > 0 ? x : 0;
}

std::string repeatString(const std::vector<int>& nums, const std::string& str) {
    if (nums.empty()) return "";
    int max_num = *std::max_element(nums.begin(), nums.end());
    std::string result;
    for (int i = 0; i < max_num; ++i) {
        result += str;
    }
    return result;
}
