SET (THIS_SRC
        main.cpp
    )

# Improve containers and algorithms
add_executable(aelib_tree_perftest ${THIS_SRC})
target_link_libraries(aelib_tree_perftest aelib_tree)
