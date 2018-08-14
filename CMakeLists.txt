# AE Library
SET(AELIB_SM_SOURCES sm/sml_event.cpp sm/sml_eventhandlerexpression.cpp sm/sml_ids.cpp sm/sml_simpleaction.cpp sm/sml_simpleguard.cpp sm/sml_state.cpp sm/sml_statemachine.cpp sm/sml_statemachineinstance.cpp)

add_library(aelib ${AELIB_SM_SOURCES})
set_target_properties(aelib PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_DEV_LIBPATH})
set_property(TARGET aelib PROPERTY CXX_STANDARD 17)

# A* Algorithm unittest
add_executable(aelib_ut_astar ai/ut/ut_astar.cpp)
target_link_libraries(aelib_ut_astar gmock_main ${CMAKE_THREAD_LIBS_INIT})
set_property(TARGET aelib_ut_astar PROPERTY CXX_STANDARD 17)

add_test(Test_AStar aelib_ut_astar)

# Statemachine unittests
add_executable(aelib_ut_sm sm/ut/ut_sm.cpp)
target_link_libraries(aelib_ut_sm gmock_main ${CMAKE_THREAD_LIBS_INIT} aelib)
set_property(TARGET aelib_ut_sm PROPERTY CXX_STANDARD 17)

add_test(Test_SM aelib_ut_sm)

# Binary Tree unittests
add_executable(aelib_ut_tree tree/ut/UTEmptyTree.cpp tree/ut/UTEraseItem.cpp tree/ut/UTInsertItem.cpp tree/ut/UTIterator.cpp tree/ut/UTTreeHelper.cpp)
target_link_libraries(aelib_ut_tree gmock_main ${CMAKE_THREAD_LIBS_INIT} aelib)
set_property(TARGET aelib_ut_tree PROPERTY CXX_STANDARD 17)

add_test(Test_Tree aelib_ut_tree)

# Improve containers and algorithms
add_executable(aelib_ut_base base/ut/ut_improve_containers.cpp base/ut/ut_algorithms.cpp)
target_link_libraries(aelib_ut_base gmock_main ${CMAKE_THREAD_LIBS_INIT} aelib)
set_property(TARGET aelib_ut_base PROPERTY CXX_STANDARD 17)

add_test(Test_Base aelib_ut_base)

# Observer Pattern
add_executable(aelib_ut_observer base/ut/ut_observer.cpp)
target_link_libraries(aelib_ut_observer gmock_main ${CMAKE_THREAD_LIBS_INIT} aelib)
set_property(TARGET aelib_ut_observer PROPERTY CXX_STANDARD 17)

add_test(Test_Observer aelib_ut_observer)

add_custom_target(test_aelib)
add_dependencies(test_aelib aelib_ut_astar aelib_ut_sm aelib_ut_tree aelib_ut_base aelib_ut_observer)
