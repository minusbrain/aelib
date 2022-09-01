SET (THIS_SRC
        CommonData.h
        UTEmptyTree.cpp
        UTEraseItem.cpp
        UTInsertItem.cpp
        UTIterator.cpp
        UTTreeHelper.cpp
    )

# Improve containers and algorithms
add_executable(aelib_ut_tree ${THIS_SRC})
target_link_libraries(aelib_ut_tree aelib_tree ${GTEST_LIBS_TO_LINK} ${CMAKE_THREAD_LIBS_INIT})

add_test(Test_Tree aelib_ut_tree)
