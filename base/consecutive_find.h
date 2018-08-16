#pragma once

#include <iterator>

namespace ae {
/**
* \brief Find the first occurrence of 'n' consecutive equal values in range
*
* This algorithm searches a given range for a consecutive sub-range of equal
* values
* with given length.
* Consider the following code snippet
* \code
*     std::vector<int> values = { 9, 9, 8, 8, 8, 8, 7, 7, 6, 6, 6 };
*     auto it = consecutive_find(values.begin(), values.end(), 4);
* \endcode
* The returned iterator 'it' now points to the first occurrence of '8' in the
* vector
* because it is the start of the first (and only) occurrence of 4 consecutive
* and
* equal values.
*
* This implementation has been created using help and information from the
* following
* <a
* href="http://stackoverflow.com/questions/26982371/find-multiple-adjacent-values-in-container">StackOverflow
* question</a>
*
* \param[in] begin  Iterator indicating the beginning of the range to search
* \param[in] end    Iterator indicating the end of the range to search
* \param[in] n      Number of consecutive equal items to be found
* \return    Iterator to first element of consecutive sub-range of n equal
* items.
*            'end' if no consecutive sub-range of n equal items found. In case
* of
*            'n == 0 || n == 1' 'begin' is returned.
*/
template <class Iter>
Iter consecutive_find(Iter begin, Iter end, std::size_t n) {
    std::size_t count(1);
    Iter marker, lead;

    for (marker = lead = begin; lead != end; marker = lead, count = 1) {
        for (lead = std::next(marker); (lead != end) && (*marker == *lead);
             ++count, ++lead)
            ;

        if (count >= n) {
            return marker;
        }
    }
    return marker;
}
}
