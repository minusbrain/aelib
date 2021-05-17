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

#include "CommonData.h"

TEST(UT005EraseItem, RemoveOnlyExistingItem_NoThrowAndSize0) {
    base::Tree<int> tree;
    tree.insert(32987);
    ASSERT_NO_THROW(tree.erase(tree.find(32987)));
    ASSERT_EQ(0, tree.size());
}

TEST(UT005EraseItem, RemoveOnlyExistingItem_IsEmptyTrue) {
    base::Tree<int> tree;
    tree.insert(32987);
    tree.erase(tree.find(32987));
    ASSERT_TRUE(tree.empty());
}

TEST(UT005EraseItem, RemoveOnlyExistingItem_CannotFindItem) {
    base::Tree<int> tree;
    tree.insert(32987);
    tree.erase(tree.find(32987));
    ASSERT_TRUE(tree.find(32987) == tree.end());
}

TEST(UT005EraseItem, RemoveRootItemWithOneChildRight_NoThrowSizeCorrectAndCannotFind) {
    base::Tree<int> tree;
    tree.insert(5);
    tree.insert(6);
    ASSERT_NO_THROW(tree.erase(tree.find(5)));
    ASSERT_EQ(1, tree.size());
    ASSERT_TRUE(tree.find(5) == tree.end());
    ASSERT_TRUE(tree.find(6) != tree.end());
}

TEST(UT005EraseItem, RemoveRootItemWithOneChildLeft_NoThrowSizeCorrectAndCannotFind) {
    base::Tree<int> tree;
    tree.insert(6);
    tree.insert(5);
    ASSERT_NO_THROW(tree.erase(tree.find(6)));
    ASSERT_EQ(1, tree.size());
    ASSERT_TRUE(tree.find(6) == tree.end());
    ASSERT_TRUE(tree.find(5) != tree.end());
}

TEST(UT005EraseItem, RemoveItemWithOneChildRight_NoThrowSizeCorrectAndCannotFind) {
    base::Tree<int> tree;
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

TEST(UT005EraseItem, RemoveItemWithOneChildLeft_NoThrowSizeCorrectAndCannotFind) {
    base::Tree<int> tree;
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

TEST(UT005EraseItem, RemoveRootItemWithTwoChildrenCloseZ_NoThrowSizeCorrectAndCannotFind) {
    base::Tree<int> tree;
    tree.insert(5);
    tree.insert(6);
    tree.insert(4);
    ASSERT_NO_THROW(tree.erase(tree.find(5)));
    ASSERT_EQ(2, tree.size());
    ASSERT_TRUE(tree.find(5) == tree.end());
    ASSERT_TRUE(tree.find(6) != tree.end());
    ASSERT_TRUE(tree.find(4) != tree.end());
}

TEST(UT005EraseItem, RemoveRootItemWithTwoChildrenFarZ_NoThrowSizeCorrectAndCannotFind) {
    base::Tree<int> tree;
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

TEST(UT005EraseItem, RemoveItemWithTwoChildrenCloseZ_NoThrowSizeCorrectAndCannotFind) {
    base::Tree<int> tree;
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

TEST(UT005EraseItem, RemoveItemWithTwoChildrenFarZ_NoThrowSizeCorrectAndCannotFind) {
    base::Tree<int> tree;
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
