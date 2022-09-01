SET (THIS_SRC
        iterator.h
        treehelper.h
        node.h
        tree.h

        dummy.cpp
    )

add_library(aelib_tree ${THIS_SRC})

add_subdirectory (ut)
add_subdirectory (perftest)
