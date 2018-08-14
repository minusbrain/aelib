#include "gtest/gtest.h"
#include <base.h>

TEST(SortedFind, IntegerVector_FindExistingValue_ExpectCorrectIterator) {
    std::vector<int> dut = {1, 2, 3, 4, 5, 6, 7, 8, 9, 89345, 999999};

    auto it =
      ae::sorted_find(dut, 5, [](auto lhs, auto rhs) { return lhs < rhs; });

    EXPECT_EQ(5, *it);
}

TEST(SortedFind, IntegerVector_FindNonExistingValue_ExpectCorrectIterator) {
    std::vector<int> dut = {1, 2, 3, 4, 6, 7, 8, 9, 89345, 999999};

    auto it =
      ae::sorted_find(dut, 5, [](auto lhs, auto rhs) { return lhs < rhs; });

    EXPECT_EQ(dut.end(), it);
}

TEST(SortedFind, EmptyVector_FindNonExistingValue_ExpectEndIterator) {
    std::vector<int> dut = {};

    auto it =
      ae::sorted_find(dut, 5, [](auto lhs, auto rhs) { return lhs < rhs; });

    EXPECT_EQ(dut.end(), it);
}

TEST(SortedFind, OneItemVector_FindExistingValue_ExpectCorrectIterator) {
    std::vector<int> dut = {5};

    auto it =
      ae::sorted_find(dut, 5, [](auto lhs, auto rhs) { return lhs < rhs; });

    EXPECT_EQ(5, *it);
}

TEST(SortedFind, OneItemVector_FindNonExistingValue_ExpectEndIterator) {
    std::vector<int> dut = {6};

    auto it =
      ae::sorted_find(dut, 5, [](auto lhs, auto rhs) { return lhs < rhs; });

    EXPECT_EQ(dut.end(), it);
}

TEST(SortedFind, LargeVector_FindExistingValue_ExpectCorrectIterator) {
    std::vector<int> dut(1000);
    std::generate(dut.begin(), dut.end(),
                  std::rand); // Using the C function rand()

    dut.push_back(3744);

    ae::sort(dut);

    auto it =
      ae::sorted_find(dut, 3744, [](auto lhs, auto rhs) { return lhs < rhs; });

    EXPECT_EQ(3744, *it);
}

TEST(SortedFind, LargeVector_FindNonExistingValue_ExpectEndIterator) {
    std::vector<int> dut(1000);
    std::generate(dut.begin(), dut.end(),
                  std::rand); // Using the C function rand()

    std::remove(dut.begin(), dut.end(), 3744);

    ae::sort(dut);

    auto it =
      ae::sorted_find(dut, 3744, [](auto lhs, auto rhs) { return lhs < rhs; });

    EXPECT_EQ(dut.end(), it);
}
