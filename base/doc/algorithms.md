# New algorithms extending STL algorithms

A collection of STL container algorithms that extend the STL algorithms
for more specific use-cases.

## consecutive_find - Find n equal consecutive elements

This algorithm searches a given range for a consecutive sub-range of equal values
with given length. Consider the following code snippet
```cpp
    #include <base/consecutive_find.h>

    std::vector<int> values = { 9, 9, 8, 8, 8, 8, 7, 7, 6, 6, 6 };
    auto it = base::consecutive_find(values.begin(), values.end(), 4);
    assert (it == values.begin() + 2);
```

The returned iterator `it` now points to the first occurrence of `8` in the vector
because it is the start of the first (and only) occurrence of four consecutive and
equal values.

## find_last - Find last matching element in a container

This algorithm searches a given range for a given value and returns
an iterator to the last occurence of it. Consider the following code snippet
```cpp
    #include <base/find_last.h>

    std::vector<int> values = { 5, 13, 5, 22, 5, 7 };
    auto it = base::find_last(values.begin(), values.end(), 5);
    assert (it == values.begin() + 4);
```
The returned iterator `it` now points to the last occurrence of `5` in the vector

## sorted_find - Binary search find in sorted container

Finds a value in a pre-sorted container. Supports custom comparison functions.

```cpp
    #include <base/sorted_find.h>

    std::vector<int> dut(1000);
    auto ascending = [](auto lhs, auto rhs) { return lhs < rhs; };
    auto descending = [](auto lhs, auto rhs) { return lhs < rhs; };
    std::generate(dut.begin(), dut.end(), std::rand);
    dut.push_back(3744);

    base::sort(dut, ascending);
    auto it = base::sorted_find(dut, 3744, ascending);
    EXPECT_EQ(3744, *it);

    base::sort(dut, descending);
    auto it = base::sorted_find(dut, 3744, descending);
    EXPECT_EQ(dut.end(), it);
```

Returns an iterator pointing to value if found or to end() of container if not found. In case container
is not sorted, behavior is undefined. In case the value occurs more than once in the container
the iterator points to one of the instances of the value. It is undefined which of the
instances this is.

## transform_if - Conditionally transform each element of an input range to an output container

This algorithm transforms each element of an input range matching a provided predicate
into a new container using the provided transformation function.

Consider the following code snippet
```cpp
    #include <base/transform_if.h>

    auto transIntHalf = [](int in) -> int { return (int)(in / 2); };
    auto predIfEven = [](int in) -> bool { return (in % 2) == 0; };

    std::vector<int> vecIn{1, 4, 3, 2, 1, 8, 2, 1};
    std::vector<int> vecOut{};

    base::transform_if(vecIn.begin(), vecIn.end(), std::back_inserter(vecOut),
                        transIntHalf, predIfEven);
```
`vecOut` now contains `{2, 1, 4, 1}`. Half of every even integer in the original
vector
