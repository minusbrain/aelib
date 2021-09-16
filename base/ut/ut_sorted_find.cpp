/**
 * @author     Andreas Evers
 *
 * @copyright  Copyright © 2020 Andreas Evers
 *
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this
 * software and associated documentation files (the “Software”), to deal in the Software
 * without restriction, including without limitation the rights to use, copy, modify,
 * merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies
 * or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR
 * THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#include <base/improve_containers.h>
#include <base/sorted_find.h>

#include "gtest/gtest.h"

TEST(SortedFind, IntegerVector_FindExistingValue_ExpectCorrectIterator) {
    std::vector<int> dut = {1, 2, 3, 4, 5, 6, 7, 8, 9, 89345, 999999};

    auto it = base::sorted_find(dut, 5, [](auto lhs, auto rhs) { return lhs < rhs; });

    EXPECT_EQ(5, *it);
}

TEST(SortedFind, IntegerVector_FindNonExistingValue_ExpectCorrectIterator) {
    std::vector<int> dut = {1, 2, 3, 4, 6, 7, 8, 9, 89345, 999999};

    auto it = base::sorted_find(dut, 5, [](auto lhs, auto rhs) { return lhs < rhs; });

    EXPECT_EQ(dut.end(), it);
}

TEST(SortedFind, EmptyVector_FindNonExistingValue_ExpectEndIterator) {
    std::vector<int> dut = {};

    auto it = base::sorted_find(dut, 5, [](auto lhs, auto rhs) { return lhs < rhs; });

    EXPECT_EQ(dut.end(), it);
}

TEST(SortedFind, OneItemVector_FindExistingValue_ExpectCorrectIterator) {
    std::vector<int> dut = {5};

    auto it = base::sorted_find(dut, 5, [](auto lhs, auto rhs) { return lhs < rhs; });

    EXPECT_EQ(5, *it);
}

TEST(SortedFind, OneItemVector_FindNonExistingValue_ExpectEndIterator) {
    std::vector<int> dut = {6};

    auto it = base::sorted_find(dut, 5, [](auto lhs, auto rhs) { return lhs < rhs; });

    EXPECT_EQ(dut.end(), it);
}

TEST(SortedFind, LargeVector_FindExistingValue_ExpectCorrectIterator) {
    std::vector<int> dut(1000);
    std::generate(dut.begin(), dut.end(),
                  std::rand);  // Using the C function rand()

    dut.push_back(3744);

    base::sort(dut);

    auto it = base::sorted_find(dut, 3744, [](auto lhs, auto rhs) { return lhs < rhs; });

    EXPECT_EQ(3744, *it);
}

TEST(SortedFind, LargeVector_FindNonExistingValue_ExpectEndIterator) {
    std::vector<int> dut(1000);
    std::generate(dut.begin(), dut.end(),
                  std::rand);  // Using the C function rand()

    (void)std::remove(dut.begin(), dut.end(), 3744);

    base::sort(dut);

    auto it = base::sorted_find(dut, 3744, [](auto lhs, auto rhs) { return lhs < rhs; });

    EXPECT_EQ(dut.end(), it);
}
