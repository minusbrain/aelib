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
#include <tree/treehelper.h>

#include <string>

#include "CommonData.h"
#include "gtest/gtest.h"

TEST(UT002TreeHelper, LeftRotateSubtree_ExpectCorrectTreeStructureAfterRotation) {
    /* Before
     *             root
     *                 \
     *                  r1
     *                 /  \
     *              rl2    r2
     *
     * After leftRotating over "root"
     *           r1
     *          /  \
     *      root    r2
     *        \
     *         rl2
     */
    base::Node<std::string> nodeRoot(nullptr, "root");
    base::Node<std::string> nodeR1(&nodeRoot, "r1");
    base::Node<std::string> nodeR2(&nodeR1, "r2");
    base::Node<std::string> nodeRL2(&nodeR1, "rl2");
    base::Node<std::string>* newRoot;

    nodeRoot.setRightChild(&nodeR1);
    nodeR1.setRightChild(&nodeR2);
    nodeR1.setLeftChild(&nodeRL2);

    newRoot = base::TreeHelper<std::string>::leftRotateSubtree(&nodeRoot);
    // Check if all nodes are present and at correct location
    ASSERT_TRUE(newRoot != nullptr);
    EXPECT_STREQ("r1", newRoot->getPayload().c_str());
    ASSERT_TRUE(newRoot->getLeftChild() != nullptr);
    EXPECT_STREQ("root", newRoot->getLeftChild()->getPayload().c_str());
    ASSERT_TRUE(newRoot->getLeftChild()->getRightChild() != nullptr);
    EXPECT_STREQ("rl2", newRoot->getLeftChild()->getRightChild()->getPayload().c_str());
    ASSERT_TRUE(newRoot->getRightChild() != nullptr);
    EXPECT_STREQ("r2", newRoot->getRightChild()->getPayload().c_str());

    // Check if leafs are actually leafs and have no children
    EXPECT_TRUE(newRoot->getRightChild()->getRightChild() == nullptr);
    EXPECT_TRUE(newRoot->getRightChild()->getLeftChild() == nullptr);
    EXPECT_TRUE(newRoot->getLeftChild()->getLeftChild() == nullptr);
    EXPECT_TRUE(newRoot->getLeftChild()->getRightChild()->getLeftChild() == nullptr);
    EXPECT_TRUE(newRoot->getLeftChild()->getRightChild()->getRightChild() == nullptr);

    // Check if all parents are correctly set
    EXPECT_STREQ("r1", newRoot->getLeftChild()->getParent()->getPayload().c_str());
    EXPECT_STREQ("r1", newRoot->getRightChild()->getParent()->getPayload().c_str());
    EXPECT_STREQ("root", newRoot->getLeftChild()->getRightChild()->getParent()->getPayload().c_str());
}

TEST(UT002TreeHelper, RightRotateSubtree_ExpectCorrectTreeStructureAfterRotation) {
    /* Before
     *             root
     *            /
     *          l1
     *         /  \
     *       l2    lr2
     *
     * After rightRotating over "root"
     *           l1
     *          /  \
     *        l2    root
     *             /
     *          lr2
     */
    base::Node<std::string> nodeRoot(nullptr, "root");
    base::Node<std::string> nodeL1(&nodeRoot, "l1");
    base::Node<std::string> nodeL2(&nodeL1, "l2");
    base::Node<std::string> nodeLR2(&nodeL1, "lr2");
    base::Node<std::string>* newRoot;

    nodeRoot.setLeftChild(&nodeL1);
    nodeL1.setLeftChild(&nodeL2);
    nodeL1.setRightChild(&nodeLR2);

    newRoot = base::TreeHelper<std::string>::rightRotateSubtree(&nodeRoot);
    // Check if all nodes are present and at correct location
    ASSERT_TRUE(newRoot != nullptr);
    EXPECT_STREQ("l1", newRoot->getPayload().c_str());
    ASSERT_TRUE(newRoot->getRightChild() != nullptr);
    EXPECT_STREQ("root", newRoot->getRightChild()->getPayload().c_str());
    ASSERT_TRUE(newRoot->getRightChild()->getLeftChild() != nullptr);
    EXPECT_STREQ("lr2", newRoot->getRightChild()->getLeftChild()->getPayload().c_str());
    ASSERT_TRUE(newRoot->getLeftChild() != nullptr);
    EXPECT_STREQ("l2", newRoot->getLeftChild()->getPayload().c_str());

    // Check if leafs are actually leafs and have no children
    EXPECT_TRUE(newRoot->getLeftChild()->getLeftChild() == nullptr);
    EXPECT_TRUE(newRoot->getLeftChild()->getRightChild() == nullptr);
    EXPECT_TRUE(newRoot->getRightChild()->getRightChild() == nullptr);
    EXPECT_TRUE(newRoot->getRightChild()->getLeftChild()->getRightChild() == nullptr);
    EXPECT_TRUE(newRoot->getRightChild()->getLeftChild()->getLeftChild() == nullptr);

    // Check if all parents are correctly set
    EXPECT_STREQ("l1", newRoot->getRightChild()->getParent()->getPayload().c_str());
    EXPECT_STREQ("l1", newRoot->getLeftChild()->getParent()->getPayload().c_str());
    EXPECT_STREQ("root", newRoot->getRightChild()->getLeftChild()->getParent()->getPayload().c_str());
}
