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
#include <base/transform_if.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <vector>

using ::testing::ElementsAre;

auto transIntHalf = [](int in) -> int { return (int)(in / 2); };
auto transFloatHalf = [](int in) -> double { return in / 2.0; };
auto predIfEven = [](int in) -> bool { return (in % 2) == 0; };
auto predIfOdd = [](int in) -> bool { return (in % 2) == 1; };

TEST(TransformIf, TransformIntVector_EasyVectorHalfEveryEvenInteger_CorrectResultVector)
{
    //                     0  1  2  3  4  5  6  7
    std::vector<int> vecIn{1, 4, 3, 2, 1, 8, 2, 1};
    std::vector<int> vecOut{};

    base::transform_if(vecIn.begin(), vecIn.end(), std::back_inserter(vecOut),
                       transIntHalf, predIfEven);

    EXPECT_THAT(vecOut, ElementsAre(2, 1, 4, 1));
}

TEST(TransformIf, TransformIntVector_EmptyVectorHalfEveryEvenInteger_EmptyResultVector)
{
    //                     0  1  2  3  4  5  6  7
    std::vector<int> vecIn{};
    std::vector<int> vecOut{};

    base::transform_if(vecIn.begin(), vecIn.end(), std::back_inserter(vecOut),
                       transIntHalf, predIfEven);

    EXPECT_EQ(vecOut.size(), 0);
    EXPECT_THAT(vecOut, ElementsAre());
}

TEST(TransformIf, TransformIntVector_OddOnlyVectorHalfEveryEvenInteger_EmptyResultVector)
{
    //                     0  1  2  3  4  5  6  7
    std::vector<int> vecIn{1, 9, 3, 7, 1, 3, 5, 1};
    std::vector<int> vecOut{};

    base::transform_if(vecIn.begin(), vecIn.end(), std::back_inserter(vecOut),
                       transIntHalf, predIfEven);

    EXPECT_EQ(vecOut.size(), 0);
    EXPECT_THAT(vecOut, ElementsAre());
}

TEST(TransformIf,
     TransformIntVector_EasyIntVectorHalfEveryOddIntegerToDouble_CorrectResultVector)
{
    //                     0  1  2  3  4  5  6  7
    std::vector<int> vecIn{1, 4, 3, 2, 1, 8, 2, 1};
    std::vector<double> vecOut{};

    base::transform_if(vecIn.begin(), vecIn.end(), std::back_inserter(vecOut),
                       transFloatHalf, predIfOdd);

    EXPECT_THAT(vecOut, ElementsAre(0.5, 1.5, 0.5, 0.5));
}
