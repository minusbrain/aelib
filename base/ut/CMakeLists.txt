SET (THIS_SRC
        ut_find_last.cpp
        ut_consecutive_find.cpp
        ut_transform_if.cpp
        ut_flag_mask.cpp
        ut_sorted_find.cpp
        ut_improve_containers.cpp
        ut_observer.cpp
        ut_argparser.cpp
        ut_astar.cpp
        ut_scope_guard.cpp
        ut_conversion.cpp
        ut_strings.cpp
    )

# Improve containers and algorithms
add_executable(aelib_ut_base ${THIS_SRC})
target_link_libraries(aelib_ut_base ${GTEST_LIBS_TO_LINK} ${CMAKE_THREAD_LIBS_INIT})

add_test(Test_Base aelib_ut_base)
