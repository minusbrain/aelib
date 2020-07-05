SET (THIS_SRC
        astar.h

        dummy.cpp
    )

add_library(aelib_ai ${THIS_SRC})
set_property(TARGET aelib_ai PROPERTY CXX_STANDARD 17)

add_subdirectory (ut)
