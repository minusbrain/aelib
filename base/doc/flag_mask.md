# Command line argument parser (argparse)

Simple tooling to help you parse the command line parameters to your program. Best explained with an example.

## Example usage

```cpp
#include <cassert>
#include <base/argparser.h>

enum class MyFlags : char { FLAG_A = 0x01, FLAG_B = 0x02, FLAG_C = 0x40 };

TEST(flag_mask, CreateSimpleFM_UseIndexOperatorToSetAndCheckState) {
    base::flag_mask<MyFlags> flags{MyFlag::FLAG_A, MyFlag::FLAG_C};
    mask[Simple::c] = true;
    mask[Simple::a] = false;
    EXPECT_TRUE(mask[Simple::c]);
    EXPECT_FALSE(mask[Simple::a]);
}
```

```

## Future / FixMes / Todos

* Add Feature: positional arguments
* Add Feature: Sub commands
* Add Feature: Custom types
* Fix weird validity handling
