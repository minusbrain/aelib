#include "gtest/gtest.h"

#define _AE_TREE_DEBUGMODE_
#include <tree/tree.h>

#include "CommonData.h"

// TODO: Make usage of graphviz optional and make the location of the executable
// configurable
void genPngImage(const ae::Tree<int>& tree, std::string text,
                 ae::Tree<int>::iterator it) {
    static int count = 0;
    std::stringstream filenameStream;
    std::stringstream command;
    std::string filenameDot;
    std::string filenamePng;
    filenameStream << "pic_" << std::setw(5) << std::setfill('0') << count++
                   << "_" << text.c_str() << ".dot";
    filenameDot = filenameStream.str();

    std::ofstream file(filenameDot);
    tree.streamStructureToDotFormat(file, text, it);
    file.close();

    filenamePng = filenameDot;
    command << "\"C:\\Program Files (x86)\\Graphviz2.38\\bin\\dot.exe\" -Tpng "
            << filenameDot.c_str() << " > "
            << filenamePng
                 .replace(filenamePng.find(".dot"), filenamePng.size(), ".png")
                 .c_str();
    std::cout << command.str().c_str() << std::endl;
    system(command.str().c_str());
}

const int TEST_NUM_OF_ELEMENTS = 10;
const int TEST_STD_INTS[10] = {5, 3876, -37864, 0, 1, -1, 83, 345, 34256, 1234};
const int TEST_NON_STD_INTS[10] = {43,   564,   -546, 2,     45,
                                   -844, 53456, 3213, 86786, 5345};
const int TEST_UNSORTED_INTS[10] = {3, 6, 1, -10, 3876, 0, 34256, 5, 4, 2};
const int TEST_ASCENDING_INTS[10] = {-10, 0, 1, 2, 3, 4, 5, 6, 3876, 34256};
const int TEST_DESCENDING_INTS[10] = {34256, 3876, 6, 5, 4, 3, 2, 1, 0, -10};

TEST(UT003InsertItem, InsertSingleValue_getHeight_Return1) {
    ae::Tree<int> tree;
    tree.insert(32987);
    ASSERT_EQ(1, tree.getHeight());
}

TEST(UT003InsertItem, InsertSingleValue_getSize_Return1) {
    ae::Tree<int> tree;
    tree.insert(32987);
    ASSERT_EQ(1, tree.size());
}

TEST(UT003InsertItem, InsertSingleValue_getBalance_Return0) {
    ae::Tree<int> tree;
    tree.insert(32987);
    ASSERT_EQ(0, tree.getBalance());
}

TEST(UT003InsertItem, InsertBigAndSmall_getHeight_Return2) {
    ae::Tree<int> tree;
    tree.insert(32987);
    tree.insert(5);
    ASSERT_EQ(2, tree.getHeight());
}

TEST(UT003InsertItem, InsertBigAndSmall_getSize_Return2) {
    ae::Tree<int> tree;
    tree.insert(32987);
    tree.insert(5);
    ASSERT_EQ(2, tree.size());
}

TEST(UT003InsertItem, InsertBigAndSmall_getBalance_ReturnMinus1) {
    ae::Tree<int> tree;
    tree.insert(32987);
    tree.insert(5);
    ASSERT_EQ(-1, tree.getBalance());
}

TEST(UT003InsertItem, InsertSmallAndBig_getHeight_Return2) {
    ae::Tree<int> tree;
    tree.insert(5);
    tree.insert(32987);
    ASSERT_EQ(2, tree.getHeight());
}

TEST(UT003InsertItem, InsertSmallAndBig_getBalance_Return1) {
    ae::Tree<int> tree;
    tree.insert(5);
    tree.insert(32987);
    ASSERT_EQ(1, tree.getBalance());
}

TEST(UT003InsertItem, InsertNormalAndSmallAndBig_getHeight_Return2) {
    ae::Tree<int> tree;
    tree.insert(1000);
    tree.insert(5);
    tree.insert(32987);
    ASSERT_EQ(2, tree.getHeight());
}

TEST(UT003InsertItem, InsertNormalAndSmallAndBig_getSize_Return3) {
    ae::Tree<int> tree;
    tree.insert(1000);
    tree.insert(5);
    tree.insert(32987);
    ASSERT_EQ(3, tree.size());
}

TEST(UT003InsertItem, InsertNormalAndSmallAndBig_getBalance_Return0) {
    ae::Tree<int> tree;
    tree.insert(1000);
    tree.insert(5);
    tree.insert(32987);
    ASSERT_EQ(0, tree.getBalance());
}

TEST(UT003InsertItem, InsertTenValues_containsInsertedValue_ReturnTrue) {
    ae::Tree<int> tree;
    for (int i = 0; i < TEST_NUM_OF_ELEMENTS; ++i)
        tree.insert(TEST_STD_INTS[i]);

    for (int i = 0; i < TEST_NUM_OF_ELEMENTS; ++i) {
        ASSERT_TRUE(tree.contains(TEST_STD_INTS[i]));
    }
}

TEST(UT003InsertItem, InsertTenValues_getSize_Returns10) {
    ae::Tree<int> tree;
    for (int i = 0; i < TEST_NUM_OF_ELEMENTS; ++i)
        tree.insert(TEST_STD_INTS[i]);

    ASSERT_EQ(10, tree.size());
}

TEST(UT003InsertItem, InsertTenValues_containsNotInsertedValue_ReturnFalse) {
    ae::Tree<int> tree;
    for (int i = 0; i < TEST_NUM_OF_ELEMENTS; ++i)
        tree.insert(TEST_STD_INTS[i]);

    for (int i = 0; i < TEST_NUM_OF_ELEMENTS; ++i) {
        ASSERT_FALSE(tree.contains(TEST_NON_STD_INTS[i]));
    }
}

TEST(UT003InsertItem, InsertTenAscendingValues_getHeight_Return4) {
    ae::Tree<int> tree;
    for (int i = 0; i < TEST_NUM_OF_ELEMENTS; ++i)
        tree.insert(TEST_ASCENDING_INTS[i]);

    ASSERT_EQ(4, tree.getHeight());
}

TEST(UT003InsertItem,
     InsertTenAscendingValues_getBalance_ReturnAbsSmallerEqual1) {
    ae::Tree<int> tree;
    for (int i = 0; i < TEST_NUM_OF_ELEMENTS; ++i)
        tree.insert(TEST_ASCENDING_INTS[i]);

    ASSERT_LE(std::abs(tree.getBalance()), 1);
}

TEST(UT003InsertItem, InsertTenDescendingValues_getHeight_Return4) {
    ae::Tree<int> tree;
    for (int i = 0; i < TEST_NUM_OF_ELEMENTS; ++i)
        tree.insert(TEST_DESCENDING_INTS[i]);

    ASSERT_EQ(4, tree.getHeight());
}

TEST(UT003InsertItem,
     InsertTenDescendingValues_getBalance_ReturnAbsSmallerEqual1) {
    ae::Tree<int> tree;
    for (int i = 0; i < TEST_NUM_OF_ELEMENTS; ++i)
        tree.insert(TEST_DESCENDING_INTS[i]);

    ASSERT_LE(std::abs(tree.getBalance()), 1);
}

TEST(
  UT003InsertItem,
  InsertValuesToCauseLeftRightRotation_getBalance_BalanceOfRotatedRootMustBeLowerThan2) {
    ae::Tree<int> tree;

    // genPngImage(tree, "initial", tree.end());
    // tree.setDebugCallback(genPngImage);
    tree.insert(9);
    tree.insert(4);
    tree.insert(1);
    tree.insert(3);
    tree.insert(2);
    tree.insert(6);
    tree.insert(5);
    tree.insert(7);
    tree.insert(8);

    // genPngImage(tree, "final", tree.end());

    EXPECT_LT(abs(tree.getRootNode()->getRightChild()->getBalance()), 2);
}
