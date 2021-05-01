# base
C++ header only lib with basic functionalities that extend C++ STL and PocoLibraries

## STL related functions:

* consecutive_find algorithm -> Find the first occurrence of 'n' consecutive equal values in range
* find_last algorithm -> Find the last occurrence of value in range
* transform_if algorithm -> Modifies each value in a range that matches a condition
* OStream Helper -> Some helper functions to print out data using ostreams

## Poco related functions:

Preconditions:

* These functions depend on the availability of PocoLibraries on the system
* User of base lib is responsible for fulfilling this dependency via the build tooling

Functions:

* Recursive print a Poco abstract configuration object

## General purpose tools

* Registry Pattern template -> register subclasses of a baseclass identified by a String
                               and instantiate objects of them
* Manager Pattern template -> Manage (add/remove/get) instances of objects of a baseclass
* FlagMask -> A bitmask that can be used for any integer based flag type