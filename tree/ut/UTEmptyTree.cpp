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
#include "gtest/gtest.h"
#define _AE_TREE_DEBUGMODE_
#include <tree/tree.h>

TEST(UT001EmptyTree, InstantiateAndDelete_NoThrow)
{
    base::Tree<int>* tree = nullptr;
    ASSERT_NO_THROW(tree = new base::Tree<int>());
    ASSERT_NO_THROW(delete tree);
}

TEST(UT001EmptyTree, GetHeight_NoThrow)
{
    base::Tree<int> tree;
    ASSERT_NO_THROW(tree.getHeight());
}

TEST(UT001EmptyTree, GetHeight_ReturnZero)
{
    base::Tree<int> tree;
    ASSERT_EQ(0, tree.getHeight());
}

TEST(UT001EmptyTree, GetSize_NoThrow)
{
    base::Tree<int> tree;
    ASSERT_NO_THROW(tree.size());
}

TEST(UT001EmptyTree, GetSize_ReturnZero)
{
    base::Tree<int> tree;
    ASSERT_EQ(0, tree.size());
}

TEST(UT001EmptyTree, GetBalance_NoThrow)
{
    base::Tree<int> tree;
    ASSERT_NO_THROW(tree.getBalance());
}

TEST(UT001EmptyTree, GetBalance_ReturnZero)
{
    base::Tree<int> tree;
    ASSERT_EQ(0, tree.getBalance());
}

TEST(UT001EmptyTree, Contains_NoThrow)
{
    base::Tree<int> tree;
    ASSERT_NO_THROW(tree.contains(21));
}

TEST(UT001EmptyTree, Iterator_BeginNoThrow)
{
    base::Tree<int> tree;
    ASSERT_NO_THROW(tree.begin());
}

TEST(UT001EmptyTree, Iterator_EndNoThrow)
{
    base::Tree<int> tree;
    ASSERT_NO_THROW(tree.end());
}

TEST(UT001EmptyTree, Iterator_BeginEqualsEnd)
{
    base::Tree<int> tree;
    ASSERT_TRUE(tree.begin() == tree.end());
}
