# base
C++ header only lib with basic functionalities that extend C++ STL or are commonly required
for C++ based projects.

## Modules
* [Command-Line argument parsing](base/doc/argparser.md)
* [A* Star Pathfinding](base/doc/astar.md)

## STL related functions:

* consecutive_find algorithm -> Find the first occurrence of 'n' consecutive equal values in range
* find_last algorithm -> Find the last occurrence of value in range
* transform_if algorithm -> Modifies each value in a range that matches a condition
* OStream Helper -> Some helper functions to print out data using ostreams

## Registry Pattern template

Register subclasses of a baseclass identified by a String and instantiate objects of them

## Manager Pattern template

Manage (add/remove/get) instances of objects of a baseclass

## FlagMask

A bitmask that can be used for any integer based flag type