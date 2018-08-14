#include "gtest/gtest.h"
#define _AE_TREE_DEBUGMODE_
#include <aelib/tree/tree.h>

TEST(UT001EmptyTree, InstantiateAndDelete_NoThrow)
{
	ae::Tree<int>* tree = nullptr;
	ASSERT_NO_THROW(tree = new ae::Tree<int>());
	ASSERT_NO_THROW(delete tree);
}

TEST(UT001EmptyTree, GetHeight_NoThrow)
{
	ae::Tree<int> tree;
	ASSERT_NO_THROW(tree.getHeight());
}

TEST(UT001EmptyTree, GetHeight_ReturnZero)
{
	ae::Tree<int> tree;
	ASSERT_EQ(0, tree.getHeight());
}

TEST(UT001EmptyTree, GetSize_NoThrow)
{
	ae::Tree<int> tree;
	ASSERT_NO_THROW(tree.size());
}

TEST(UT001EmptyTree, GetSize_ReturnZero)
{
	ae::Tree<int> tree;
	ASSERT_EQ(0, tree.size());
}

TEST(UT001EmptyTree, GetBalance_NoThrow)
{
	ae::Tree<int> tree;
	ASSERT_NO_THROW(tree.getBalance());
}

TEST(UT001EmptyTree, GetBalance_ReturnZero)
{
	ae::Tree<int> tree;
	ASSERT_EQ(0, tree.getBalance());
}

TEST(UT001EmptyTree, Contains_NoThrow)
{
	ae::Tree<int> tree;
	ASSERT_NO_THROW(tree.contains(21));
}

TEST(UT001EmptyTree, Iterator_BeginNoThrow)
{
	ae::Tree<int> tree;
	ASSERT_NO_THROW(tree.begin());
}

TEST(UT001EmptyTree, Iterator_EndNoThrow)
{
	ae::Tree<int> tree;
	ASSERT_NO_THROW(tree.end());
}

TEST(UT001EmptyTree, Iterator_BeginEqualsEnd)
{
	ae::Tree<int> tree;
	ASSERT_TRUE(tree.begin() == tree.end());
}
