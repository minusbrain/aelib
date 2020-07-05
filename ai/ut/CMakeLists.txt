SET (THIS_SRC
        ut_astar.cpp
    )

# Improve containers and algorithms
add_executable(aelib_ut_ai ${THIS_SRC})
target_link_libraries(aelib_ut_ai aelib_ai ${GTEST_LIBS_TO_LINK} ${CMAKE_THREAD_LIBS_INIT})
set_property(TARGET aelib_ut_ai PROPERTY CXX_STANDARD 17)

add_test(Test_AI aelib_ut_ai)
