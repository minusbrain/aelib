cmake_minimum_required (VERSION 3.11)
project (aelib)

enable_testing()
set(THREADS_PREFER_PTHREAD_FLAG ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
find_package(Threads REQUIRED)
find_package(GTest REQUIRED CONFIG)
SET(GTEST_LIBS_TO_LINK GTest::gtest GTest::gmock GTest::gmock_main)

include_directories(${PROJECT_SOURCE_DIR} ${GTEST_INCLUDE_DIRS} ${Poco_INCLUDE_DIRS})


SET(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -coverage -fprofile-arcs -ftest-coverage")
SET(CMAKE_CXX_FLAGS_RELEASE "-O3")
SET(CMAKE_CXX_FLAGS "-Wall -Werror -Wextra -Wpedantic")

add_subdirectory (sm)
add_subdirectory (tree)
add_subdirectory (base)

add_custom_target(aelib_ut_all  COMMAND ${CMAKE_CTEST_COMMAND} -V)
add_dependencies(aelib_ut_all
                    aelib_ut_sm
                    aelib_ut_tree
                    aelib_ut_base
                    )
