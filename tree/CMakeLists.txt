SET (THIS_SRC
        iterator.h
        treehelper.h
        node.h
        tree.h

        dummy.cpp
    )

add_library(aelib_tree ${THIS_SRC})
set_property(TARGET aelib_tree PROPERTY CXX_STANDARD 17)

add_subdirectory (ut)
add_subdirectory (perftest)
