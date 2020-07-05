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
