# base
C++ header only lib with basic functionalities that extend C++ STL or are commonly required
for C++ based projects.

## Modules
* [Command-Line argument parsing](base/doc/argparser.md)
* [A* Star Pathfinding](base/doc/astar.md)
* [Additional STL algorithms](base/doc/algorithms.md)
    * consecutive_find - Find n equal consecutive elements
    * find_last - Find last matching element in a container
    * sorted_find - Binary search find in sorted container
    * transform_if - Conditionally transform each element of an input range to an output container

## STL related functions:

* OStream Helper -> Some helper functions to print out data using ostreams
*

## Registry Pattern template

Register subclasses of a baseclass identified by a String and instantiate objects of them

## Manager Pattern template

Manage (add/remove/get) instances of objects of a baseclass

## FlagMask

A bitmask that can be used for any integer based flag type