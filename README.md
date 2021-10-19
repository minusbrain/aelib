# base
C++ header only lib with basic functionalities that extend C++ STL or are commonly required
for C++ based projects.

## STL related functions:

* consecutive_find algorithm -> Find the first occurrence of 'n' consecutive equal values in range
* find_last algorithm -> Find the last occurrence of value in range
* transform_if algorithm -> Modifies each value in a range that matches a condition
* OStream Helper -> Some helper functions to print out data using ostreams

## Command line argument parser (argparse)

Simple tooling to help you parse the command line parameters to your program. Best explained with an example.

### Example usage

```cpp
#include <cassert>
#include <base/argparser.h>

using base::argparser;
using aot = base::argparser_option_type;

int main(int argc, char** argv) {
    try {
        // Construct a parser for program 'myapp'
        argparser parser{"myapp"};
        // Prepare parser with intended options
        parser.add_option<std::string>("configfile")
            .short_option('c')
            .long_option("cfg")
            .default_value(std::string("/etc/myapp.conf"))
            .description("Location of configuration file to use");
        parser.add_option<bool>("verbose").short_option('v').long_option("verbose").description(
            "Activate more verbose output");
        parser.add_option<int>("threads").short_option('j').mandatory().description(
            "Number of threads that shall be used for processing");

        // Checks for any logical errors in defined options
        assert(parser.all_options_valid());

        // Parse command line input
        auto parsed_args = parser.parse(args);

        if (!parsed_args.success()) {
            parser.print_help(std::cout, &parsed_args.get_errors());
            return;
        }

        std::cout << "Using configfile: " << parsed_args.get<std::string>("configfile") << std::endl;
        std::cout << "All parsed parameters: " << parsed_args.get_options() << std::endl;
    } catch (const std::exception& ex) {
        std::cout << "Parsing error: " << ex.what() << std::endl;
    }
}
```
### Support

Currently the following option types are supported:
* std::string  -> Expects and returns a std::string
* int          -> Expects and returns a decimal integer
* float/double -> Expects and returns a decimal floating point value
* bool         -> Expects no value but returns the presence (true) or absence (false) of a parameter

The following syntax variants are allowed for parameters:
* --option value
* --option=value
* -o value
* -o=value
* -ovalue

Options can have default values, can be mandatory and can have a description. Not logical combinations (e.g.
mandatory but with default value) will be rejected.

### Help

`parser.print_help(std::cout)` will print usage help to standard out (or any other ostream). The help for the 
example above looks like this
```text
Usage:
myapp -j <threads> [-c|--cfg <configfile>] [-v|--verbose]

Parameters:
-j <threads>            : Number of threads that shall be used for processing
-c | --cfg <configfile> : Location of configuration file to use
-v | --verbose          : Activate more verbose output
```

## Registry Pattern template 

Register subclasses of a baseclass identified by a String and instantiate objects of them

## Manager Pattern template 

Manage (add/remove/get) instances of objects of a baseclass

## FlagMask 

A bitmask that can be used for any integer based flag type