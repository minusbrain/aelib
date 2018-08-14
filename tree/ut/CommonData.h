#ifndef _AE_TEST_COMMONDATA_H_
#define _AE_TEST_COMMONDATA_H_

#define _AE_TREE_DEBUGMODE_
#include <aelib/tree/tree.h>

extern const int TEST_NUM_OF_ELEMENTS;

extern const int TEST_STD_INTS[10];
extern const int TEST_NON_STD_INTS[10];
extern const int TEST_UNSORTED_INTS[10];
extern const int TEST_ASCENDING_INTS[10];
extern const int TEST_DESCENDING_INTS[10];

// TODO: Make usage of graphviz optional and make the location of the executable configurable
extern void genPngImage(const ae::Tree<int>& tree, std::string text, ae::Tree<int>::iterator it);

#endif