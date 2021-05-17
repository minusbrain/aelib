/**
 * @author     Andreas Evers
 *
 * @copyright  Copyright © 2020 Andreas Evers
 *
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this
 * software and associated documentation files (the “Software”), to deal in the Software
 * without restriction, including without limitation the rights to use, copy, modify,
 * merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies
 * or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR
 * THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#pragma once
#include <algorithm>
#include <cstdlib>

namespace base {
template <class Iterator, typename Value, class Compare>
Iterator __sorted_find_helper(Iterator from, Iterator to, const Iterator end, const Value& value, Compare comp) {
    // If from points to searched value, return from
    if (!comp(*from, value) && !comp(value, *from)) return from;
    // If remaining search area is empty return end
    if (from == to) return end;

    size_t half_dist = std::distance(from, to) / 2;

    // For small remaining search scope optimize by linear search
    if (half_dist < 5) {
        while (from <= to) {
            if (comp(*from, value)) {
                from += 1;
                continue;
            }
            if (comp(value, *from)) return end;
            return from;
        }
    }
    // Else search appropriate upper or lower half of remaining search scope
    else if (comp(value, *(from + half_dist)) == true) {
        return __sorted_find_helper(from, from + half_dist, end, value, comp);
    } else {
        return __sorted_find_helper(from + half_dist, to, end, value, comp);
    }
    return end;  // Never reached code
}
/**
 * @brief      Finds a value in a sorted container using binary search
 *
 * @param[in]  cont       Container, must be sorted
 * @param[in]  value      Value to search
 * @param[in]  comp       Comparison function container is sorted by
 *
 * @tparam     Container  Type of container used
 * @tparam     Value      Type of value stored in container
 * @tparam     Compare    Compare callable (lambda, std::function, functor...)
 *
 * @return     Iterator pointing to value if found or to end() of container if
 *             not found. In case container is not sorted, behavior is
 *             undefined. In case the value occurs more than once in the
 *             container the iterator points to one of the instances of the
 *             value. It is undefined which of the instances this is.
 */
template <class Container, typename Value, class Compare>
typename Container::const_iterator sorted_find(const Container& cont, const Value& value, Compare comp) {
    auto begin = cont.cbegin();
    auto end = cont.cend();
    // In case the container is empty or the value is before the first entry
    // or the value is behind the last entry. Directly leave the search
    if (cont.size() == 0 || comp(value, *begin) || comp(*(end - 1), value)) return end;
    // Otherwise call the recursive helper function
    return __sorted_find_helper(begin, end - 1, end, value, comp);
}
}  // namespace base
