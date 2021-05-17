SET (THIS_SRC
        actionmock.h
        ut_sm.h
        ut_sm.cpp
    )

# Improve containers and algorithms
add_executable(aelib_ut_sm ${THIS_SRC})
target_link_libraries(aelib_ut_sm aelib_sm ${GTEST_LIBS_TO_LINK} ${CMAKE_THREAD_LIBS_INIT})
set_property(TARGET aelib_ut_sm PROPERTY CXX_STANDARD 17)

add_test(Test_SM aelib_ut_sm)
