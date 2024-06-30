#include "Helpers.hpp"
#include "UnitTests.hpp"

TEST_CASE(Dummy_test1) {
    double value = 0.0;
    auto result = dummyFunc(value);
    ASSERT_EQ(result, 1.0);  
}

TEST_CASE(Test_repeatString_with_non_empty_vector) {
    std::vector<int> nums = {0, 2, 1};
    ASSERT_EQ(repeatString(nums, "home"), "homehome");
}

TEST_CASE(Test_repeatString_with_empty_vector) {
    std::vector<int> nums = {};
    ASSERT_EQ(repeatString(nums, "home"), "");
}

TEST_CASE(Test_repeatString_with_vector_containing_zeroes) {
    std::vector<int> nums = {0, 0, 0};
    ASSERT_EQ(repeatString(nums, "home"), "");
}

TEST_CASE(Test_repeatString_with_vector_containing_negative_numbers) {
    std::vector<int> nums = {-1, -2, -3};
    ASSERT_EQ(repeatString(nums, "home"), "");
}

TEST_CASE(Test_repeatString_with_vector_containing_large_number) {
    std::vector<int> nums = {1, 5, 3};
    ASSERT_EQ(repeatString(nums, "home"), "homehomehomehomehome");
}

int main() {
    UnitTests::RunAllTests();
    return 0;
}
