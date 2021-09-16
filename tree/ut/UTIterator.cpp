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
#include <random>
#include <vector>

#include "gtest/gtest.h"

#define _AE_TREE_DEBUGMODE_
#include <tree/tree.h>

#include "CommonData.h"

// const int TEST_NUM_OF_ELEMENTS = 10;
// const int TEST_STD_INTS[10] =        {     5, 3876, -37864,   0,     1,   -1,
// 83,  345, 34256,  1234 };
// const int TEST_NON_STD_INTS[10] =    {    43,  564,   -546,   2,    45, -844,
// 53456, 3213, 86786,  5345 };
// const int TEST_UNSORTED_INTS[10] =   {     3,    6,      1, -10   3876,    0,
// 34256,    5,     4,     2 };
// const int TEST_ASCENDING_INTS[10] =  {   -10,    0,      1,   2,     3,    4,
// 5,    6,  3876, 34256 };
// const int TEST_DESCENDING_INTS[10] = { 34256, 3876,      6,   5,     4,    3,
// 2,    1,     0,   -10 };

const int NUM_OF_NODES = 1000;

TEST(UT004Iterator, InsertOneItem_beginIterator_NotEqualToEnd) {
    base::Tree<int> tree;
    tree.insert(32987);
    ASSERT_TRUE(tree.begin() != tree.end());
}

TEST(UT004Iterator, InsertOneItem_beginIteratorIncrementOnce_EqualToEnd) {
    base::Tree<int> tree;
    tree.insert(32987);
    auto it = tree.begin();
    ++it;
    ASSERT_TRUE(it == tree.end());
}

TEST(UT004Iterator, InsertTenUnsortedItems_PreIncrement_CorrectTenSortedIntsReturned) {
    base::Tree<int> tree;
    std::vector<int> ascending;

    for (int i = 0; i < TEST_NUM_OF_ELEMENTS; ++i) {
        tree.insert(TEST_UNSORTED_INTS[i]);
    }
    for (base::Tree<int>::iterator it = tree.begin(); it != tree.end(); ++it) {
        ascending.push_back((int)*it);
    }

    for (int i = 0; i < TEST_NUM_OF_ELEMENTS; ++i) {
        ASSERT_EQ(TEST_ASCENDING_INTS[i], ascending[i]);
    }
}

TEST(UT004Iterator, DescendingTree_InsertTenUnsortedItems_PreIncrement_CorrectTenSortedIntsReturned) {
    base::Tree<int> tree([](int i, int j) -> bool { return i > j; });
    std::vector<int> ascending;

    for (int i = 0; i < TEST_NUM_OF_ELEMENTS; ++i) {
        tree.insert(TEST_UNSORTED_INTS[i]);
    }
    for (base::Tree<int>::iterator it = tree.begin(); it != tree.end(); ++it) {
        ascending.push_back((int)*it);
    }

    for (int i = 0; i < TEST_NUM_OF_ELEMENTS; ++i) {
        ASSERT_EQ(TEST_DESCENDING_INTS[i], ascending[i]);
    }
}

TEST(UT004Iterator, InsertTenUnsortedItems_PostIncrement_CorrectTenSortedIntsReturned) {
    base::Tree<int> tree;
    std::vector<int> ascending;

    for (int i = 0; i < TEST_NUM_OF_ELEMENTS; ++i) {
        tree.insert(TEST_UNSORTED_INTS[i]);
    }
    for (base::Tree<int>::iterator it = tree.begin(); it != tree.end(); it++) {
        ascending.push_back((int)*it);
    }

    for (int i = 0; i < TEST_NUM_OF_ELEMENTS; ++i) {
        ASSERT_EQ(TEST_ASCENDING_INTS[i], ascending[i]);
    }
}

TEST(UT004Iterator, DescendingTree_InsertTenUnsortedItems_PostIncrement_CorrectTenSortedIntsReturned) {
    base::Tree<int> tree([](int i, int j) -> bool { return i > j; });
    std::vector<int> ascending;

    for (int i = 0; i < TEST_NUM_OF_ELEMENTS; ++i) {
        tree.insert(TEST_UNSORTED_INTS[i]);
    }
    for (base::Tree<int>::iterator it = tree.begin(); it != tree.end(); it++) {
        ascending.push_back((int)*it);
    }

    for (int i = 0; i < TEST_NUM_OF_ELEMENTS; ++i) {
        ASSERT_EQ(TEST_DESCENDING_INTS[i], ascending[i]);
    }
}

TEST(UT004Iterator, Random1000Values_InsertAndCompareWithStlSet_ExpectSameSequence) {
    std::default_random_engine randEngine;
    std::uniform_int_distribution<int> randDist(-1000000, 1000000);
    std::multiset<int> stlTree;
    base::Tree<int> myTree;
    std::multiset<int>::iterator stlIt;
    base::Tree<int>::iterator myIt;
    int currentRand = 0;

    // Fill vector with NUM_OF_NODES million integers between - 1 million and +
    // 1 million
    for (int i = 0; i < NUM_OF_NODES; ++i) {
        currentRand = randDist(randEngine);
        stlTree.insert(currentRand);
        myTree.insert(currentRand);
    }

    stlIt = stlTree.begin();
    myIt = myTree.begin();

    for (int i = 0; i < NUM_OF_NODES; ++i) {
        EXPECT_EQ(*stlIt, *myIt);
        ++stlIt;
        ++myIt;
    }

    EXPECT_TRUE(myIt == myTree.end());
}

TEST(UT004Iterator, InsertOneItem_IteratorDereferencePostIncrement_NoErrorAndCorrectValue) {
    base::Tree<int> tree;
    tree.insert(32987);
    auto it = tree.begin();
    ASSERT_EQ(32987, *(it++));
    EXPECT_TRUE(it == tree.end());
}
