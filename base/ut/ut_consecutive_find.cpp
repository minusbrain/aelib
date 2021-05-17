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
#include <base/consecutive_find.h>
#include <gtest/gtest.h>

#include <vector>

/**
 * \brief Find the first occurrence of 'n' consecutive equal values in range
 *
 * This algorithm searches a given range for a consecutive sub-range of equal values
 * with given length.
 * Consider the following code snippet
 * \code
 *     std::vector<int> values = { 9, 9, 8, 8, 8, 8, 7, 7, 6, 6, 6 };
 *     auto it = consecutive_find(values.begin(), values.end(), 4);
 * \endcode
 * The returned iterator 'it' now points to the first occurrence of '8' in the vector
 * because it is the start of the first (and only) occurrence of 4 consecutive and
 * equal values.
 *
 * This implementation has been created using help and information from the following
 * <a
 * href="http://stackoverflow.com/questions/26982371/find-multiple-adjacent-values-in-container">StackOverflow
 * question</a>
 *
 * \param[in] begin  Iterator indicating the beginning of the range to search
 * \param[in] end    Iterator indicating the end of the range to search
 * \param[in] n      Number of consecutive equal items to be found
 * \return    Iterator to first element of consecutive sub-range of n equal items.
 *            'end' if no consecutive sub-range of n equal items found. In case of
 *            'n == 0 || n == 1' 'begin' is returned.
template <class Iter>
inline Iter consecutive_find(Iter begin, Iter end, std::size_t n)
*/

TEST(ConsecutiveFind, VectorInt_EmptyFindStreakOf5_ReturnEnd) {
    //                   0  1  2  3  4  5  6  7
    std::vector<int> vec{};

    auto expected_it = vec.end();

    EXPECT_EQ(base::consecutive_find(vec.begin(), vec.end(), 5), expected_it);
}

TEST(ConsecutiveFind, VectorInt_EmptyFindStreakOf1_ReturnEnd) {
    //                   0  1  2  3  4  5  6  7
    std::vector<int> vec{};

    auto expected_it = vec.end();

    EXPECT_EQ(base::consecutive_find(vec.begin(), vec.end(), 1), expected_it);
}

TEST(ConsecutiveFind, VectorInt_EmptyFindStreakOf0_ReturnEnd) {
    //                   0  1  2  3  4  5  6  7
    std::vector<int> vec{};

    auto expected_it = vec.end();

    EXPECT_EQ(base::consecutive_find(vec.begin(), vec.end(), 0), expected_it);
}

TEST(ConsecutiveFind, VectorInt_Size1FindStreakOf5_ReturnEnd) {
    //                   0  1  2  3  4  5  6  7
    std::vector<int> vec{5};

    auto expected_it = vec.end();

    EXPECT_EQ(base::consecutive_find(vec.begin(), vec.end(), 5), expected_it);
}

TEST(ConsecutiveFind, VectorInt_Size1FindStreakOf1_ReturnBegin) {
    //                   0  1  2  3  4  5  6  7
    std::vector<int> vec{5};

    auto expected_it = vec.begin();

    EXPECT_EQ(base::consecutive_find(vec.begin(), vec.end(), 1), expected_it);
}

TEST(ConsecutiveFind, VectorInt_Size1FindStreakOf0_ReturnBegin) {
    //                   0  1  2  3  4  5  6  7
    std::vector<int> vec{5};

    auto expected_it = vec.begin();

    EXPECT_EQ(base::consecutive_find(vec.begin(), vec.end(), 0), expected_it);
}

TEST(ConsecutiveFind, VectorInt_Size5StreakOf5FindStreakOf5_ReturnBegin) {
    //                   0  1  2  3  4  5  6  7
    std::vector<int> vec{5, 5, 5, 5, 5};

    auto expected_it = vec.begin();

    EXPECT_EQ(base::consecutive_find(vec.begin(), vec.end(), 5), expected_it);
}

TEST(ConsecutiveFind, VectorInt_Size5StreakOf4FindStreakOf5_ReturnEnd) {
    //                   0  1  2  3  4  5  6  7
    std::vector<int> vec{4, 5, 5, 5, 5};

    auto expected_it = vec.end();

    EXPECT_EQ(base::consecutive_find(vec.begin(), vec.end(), 5), expected_it);
}

TEST(ConsecutiveFind, VectorInt_Size6StreakOf4AtStartFindStreakOf4_ReturnBegin) {
    //                   0  1  2  3  4  5  6  7
    std::vector<int> vec{5, 5, 5, 5, 4, 4};

    auto expected_it = vec.begin();

    EXPECT_EQ(base::consecutive_find(vec.begin(), vec.end(), 4), expected_it);
}

TEST(ConsecutiveFind, VectorInt_Size6StreakOf4InMidFindStreakOf4_CorrectIterator) {
    //                   0  1  2  3  4  5  6  7
    std::vector<int> vec{4, 5, 5, 5, 5, 4};

    auto expected_it = vec.begin() + 1;

    EXPECT_EQ(base::consecutive_find(vec.begin(), vec.end(), 4), expected_it);
}

TEST(ConsecutiveFind, VectorInt_Size6StreakOf4AtEndFindStreakOf4_CorrectIterator) {
    //                   0  1  2  3  4  5  6  7
    std::vector<int> vec{4, 4, 5, 5, 5, 5};

    auto expected_it = vec.begin() + 2;

    EXPECT_EQ(base::consecutive_find(vec.begin(), vec.end(), 4), expected_it);
}

TEST(ConsecutiveFind, VectorInt_MultipleStreaksOf4FindStreakOf4_FindFirstStreak) {
    //                   0  1  2  3  4  5  6  7, 8, 9
    std::vector<int> vec{0, 4, 4, 4, 4, 7, 5, 5, 5, 5, 0};

    auto expected_it = vec.begin() + 1;

    EXPECT_EQ(base::consecutive_find(vec.begin(), vec.end(), 4), expected_it);
}
