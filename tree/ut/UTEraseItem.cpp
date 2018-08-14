#include "gtest/gtest.h"

#define _AE_TREE_DEBUGMODE_
#include <aelib/tree/tree.h>

#include "CommonData.h"


TEST(UT005EraseItem, RemoveOnlyExistingItem_NoThrowAndSize0)
{
	ae::Tree<int> tree;
	tree.insert(32987);
	ASSERT_NO_THROW(tree.erase(tree.find(32987)));
	ASSERT_EQ(0, tree.size());
}

TEST(UT005EraseItem, RemoveOnlyExistingItem_IsEmptyTrue)
{
	ae::Tree<int> tree;
	tree.insert(32987);
	tree.erase(tree.find(32987));
	ASSERT_TRUE(tree.empty());
}

TEST(UT005EraseItem, RemoveOnlyExistingItem_CannotFindItem)
{
	ae::Tree<int> tree;
	tree.insert(32987);
	tree.erase(tree.find(32987));
	ASSERT_TRUE(tree.find(32987) == tree.end());
}

TEST(UT005EraseItem, RemoveRootItemWithOneChildRight_NoThrowSizeCorrectAndCannotFind)
{
	ae::Tree<int> tree;
	tree.insert(5);
	tree.insert(6);
	ASSERT_NO_THROW(tree.erase(tree.find(5)));
	ASSERT_EQ(1, tree.size());
	ASSERT_TRUE(tree.find(5) == tree.end());
	ASSERT_TRUE(tree.find(6) != tree.end());
}

TEST(UT005EraseItem, RemoveRootItemWithOneChildLeft_NoThrowSizeCorrectAndCannotFind)
{
	ae::Tree<int> tree;
	tree.insert(6);
	tree.insert(5);
	ASSERT_NO_THROW(tree.erase(tree.find(6)));
	ASSERT_EQ(1, tree.size());
	ASSERT_TRUE(tree.find(6) == tree.end());
	ASSERT_TRUE(tree.find(5) != tree.end());
}

TEST(UT005EraseItem, RemoveItemWithOneChildRight_NoThrowSizeCorrectAndCannotFind)
{
	ae::Tree<int> tree;
	tree.insert(10);
	tree.insert(9);
	tree.insert(11);
	tree.insert(12);
	ASSERT_NO_THROW(tree.erase(tree.find(11)));
	ASSERT_EQ(3, tree.size());
	ASSERT_TRUE(tree.find(11) == tree.end());
	ASSERT_TRUE(tree.find(12) != tree.end());
	ASSERT_TRUE(tree.find(10) != tree.end());
}

TEST(UT005EraseItem, RemoveItemWithOneChildLeft_NoThrowSizeCorrectAndCannotFind)
{
	ae::Tree<int> tree;
	tree.insert(10);
	tree.insert(9);
	tree.insert(11);
	tree.insert(8);
	ASSERT_NO_THROW(tree.erase(tree.find(9)));
	ASSERT_EQ(3, tree.size());
	ASSERT_TRUE(tree.find(9) == tree.end());
	ASSERT_TRUE(tree.find(8) != tree.end());
	ASSERT_TRUE(tree.find(10) != tree.end());
}

TEST(UT005EraseItem, RemoveRootItemWithTwoChildrenCloseZ_NoThrowSizeCorrectAndCannotFind)
{
	ae::Tree<int> tree;
	tree.insert(5);
	tree.insert(6);
	tree.insert(4);
	ASSERT_NO_THROW(tree.erase(tree.find(5)));
	ASSERT_EQ(2, tree.size());
	ASSERT_TRUE(tree.find(5) == tree.end());
	ASSERT_TRUE(tree.find(6) != tree.end());
	ASSERT_TRUE(tree.find(4) != tree.end());
}

TEST(UT005EraseItem, RemoveRootItemWithTwoChildrenFarZ_NoThrowSizeCorrectAndCannotFind)
{
	ae::Tree<int> tree;
	tree.insert(6);
	tree.insert(8);
	tree.insert(4);
	tree.insert(10);
	tree.insert(2);
	tree.insert(7);
	tree.insert(5);
	ASSERT_NO_THROW(tree.erase(tree.find(6)));
	ASSERT_EQ(6, tree.size());
	ASSERT_TRUE(tree.find(6) == tree.end());
	ASSERT_TRUE(tree.find(5) != tree.end());
	ASSERT_TRUE(tree.find(7) != tree.end());
}

TEST(UT005EraseItem, RemoveItemWithTwoChildrenCloseZ_NoThrowSizeCorrectAndCannotFind)
{
	ae::Tree<int> tree;
	tree.insert(100);
	tree.insert(50);
	tree.insert(150);
	tree.insert(25);
	tree.insert(75);
	tree.insert(125);
	tree.insert(175);
	ASSERT_NO_THROW(tree.erase(tree.find(150)));
	ASSERT_EQ(6, tree.size());
	ASSERT_TRUE(tree.find(150) == tree.end());
	ASSERT_TRUE(tree.find(125) != tree.end());
	ASSERT_TRUE(tree.find(175) != tree.end());
	ASSERT_TRUE(tree.find(100) != tree.end());
	ASSERT_TRUE(tree.find(50) != tree.end());
}

TEST(UT005EraseItem, RemoveItemWithTwoChildrenFarZ_NoThrowSizeCorrectAndCannotFind)
{
	ae::Tree<int> tree;
	tree.insert(100);
	tree.insert(50);
	tree.insert(150);
	tree.insert(25);
	tree.insert(75);
	tree.insert(125);
	tree.insert(175);
	tree.insert(12);
	tree.insert(40);
	tree.insert(60);
	tree.insert(90);
	tree.insert(140);
	tree.insert(70);
	ASSERT_NO_THROW(tree.erase(tree.find(50)));
	ASSERT_EQ(12, tree.size());
	ASSERT_TRUE(tree.find(50) == tree.end());
	ASSERT_TRUE(tree.find(25) != tree.end());
	ASSERT_TRUE(tree.find(75) != tree.end());
	ASSERT_TRUE(tree.find(60) != tree.end());
	ASSERT_TRUE(tree.find(70) != tree.end());
}
