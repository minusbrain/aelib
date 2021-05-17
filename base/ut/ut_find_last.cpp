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
#include <base/find_last.h>
#include <gtest/gtest.h>

#include <vector>

TEST(FindLast, FindLastInt_Easy_CorrectIterator) {
    //                   0  1  2  3  4  5  6  7
    std::vector<int> vec{1, 4, 3, 2, 1, 3, 2, 1};

    auto expected_last_1 = vec.begin() + 7;
    auto expected_last_2 = vec.begin() + 6;
    auto expected_last_3 = vec.begin() + 5;
    auto expected_last_4 = vec.begin() + 1;

    EXPECT_EQ(base::find_last(vec.begin(), vec.end(), 1), expected_last_1);
    EXPECT_EQ(base::find_last(vec.begin(), vec.end(), 2), expected_last_2);
    EXPECT_EQ(base::find_last(vec.begin(), vec.end(), 3), expected_last_3);
    EXPECT_EQ(base::find_last(vec.begin(), vec.end(), 4), expected_last_4);
}

TEST(FindLast, FindLastInt_LastOccurenceIsFirst_CorrectIterator) {
    //                   0  1  2  3  4  5  6  7
    std::vector<int> vec{5, 4, 3, 2, 1, 3, 2, 1};

    auto expected_last = vec.begin();

    EXPECT_EQ(base::find_last(vec.begin(), vec.end(), 5), expected_last);
}

TEST(FindLast, FindLastInt_LastOccurenceIsLast_CorrectIterator) {
    //                   0  1  2  3  4  5  6  7
    std::vector<int> vec{1, 4, 3, 2, 1, 3, 2, 5};

    auto expected_last = vec.begin() + 7;

    EXPECT_EQ(base::find_last(vec.begin(), vec.end(), 5), expected_last);
}

TEST(FindLast, FindLastInt_IntegerDoesNotoccur_EndIterator) {
    //                   0  1  2  3  4  5  6  7
    std::vector<int> vec{1, 4, 3, 2, 1, 3, 2, 1};

    auto expected_last = vec.end();

    EXPECT_EQ(base::find_last(vec.begin(), vec.end(), 5), expected_last);
}

TEST(FindLast, FindLastInt_EmptyRange_EndIterator) {
    std::vector<int> vec{};

    auto expected_last = vec.end();

    EXPECT_EQ(base::find_last(vec.begin(), vec.end(), 5), expected_last);
}

// Sequence of set iterators is undefined so we can only check if the
// content, the iterator points to, is correct
TEST(FindLast, FindLastInt_UseSet_IteratorShouldPointToCorrectValue) {
    //                  0  1  2  3  4  5  6  7
    std::set<int> myset{5, 4, 3, 2, 1, 3, 2, 1};

    EXPECT_EQ(*(base::find_last(myset.begin(), myset.end(), 2)), 2);
}
