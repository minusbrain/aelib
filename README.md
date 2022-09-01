# Introduction

aelib is a collection of classes, templates and functions that are intended as a extension
of the STL for my personal use in various C++ projects. It has been created to reduce code
duplicaiton in my projects and make my live easier.
I could also use other similar libraries for some of these things (boost, abseil, ...) but
I like doing stuff on my own in order to practice my skills and learn stuff.

The library consists of the following modules:

* base - Lots of small basic classes, templates and functions for common use cases
* sm -  A StateMachine pattern implementation
* tree - AVL Tree implementation
* log - Nothing yet :)

# Support

* Currently only tested under Linux

# Dependencies

* C++17 supporting compiler (tested with gcc and clang)
* CMake >= 3.1
* googletest and pthread for unit-tests

# base - Helper classes, templates, functions, algorithms

C++ header only lib with basic functionalities that extend C++ STL or are commonly required
for C++ based projects.

## Sub-Modules

* [Command-Line argument parsing](base/doc/argparser.md)
* [A* Star Pathfinding](base/doc/astar.md)
* [Additional STL algorithms](base/doc/algorithms.md)
    * consecutive_find - Find n equal consecutive elements
    * find_last - Find last matching element in a container
    * sorted_find - Binary search find in sorted container
    * transform_if - Conditionally transform each element of an input range to an output container
    * ostream helpers - Some helper functions to print out data using ostreams
    * ...
* Registry Pattern - Register subclasses of a baseclass identified by a String and instantiate objects of them
* Manager Pattern - Manage (add/remove/get) instances of objects of a baseclass
* FlagMask - Bitmask that can be used for any integer based flag type (enums, ...)

# sm - StateMachine Pattern

tbd

# tree - AVL Tree implementation

tbd

# License

[Published under MIT License](LICENSE)