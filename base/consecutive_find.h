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

#include <cstddef>
#include <iterator>

namespace base {
/**
 * \brief Find the first occurrence of 'n' consecutive equal values in range
 *
 * This algorithm searches a given range for a consecutive sub-range of equal values
 * with given length.
 * Consider the following code snippet
 * \code
 *     std::vector<int> values = { 9, 9, 8, 8, 8, 8, 7, 7, 6, 6, 6 };
 *     auto it = consecutive_find(values.begin(), values.end(), 4);
 * \endcode
 * The returned iterator 'it' now points to the first occurrence of '8' in the vector
 * because it is the start of the first (and only) occurrence of 4 consecutive and
 * equal values.
 *
 * This implementation has been created using help and information from the following
 * <a
 * href="http://stackoverflow.com/questions/26982371/find-multiple-adjacent-values-in-container">StackOverflow
 * question</a>
 *
 * \param[in] first  Iterator indicating the beginning of the range to search
 * \param[in] last   Iterator indicating the end of the range to search
 * \param[in] n      Number of consecutive equal items to be found
 * \return    Iterator to first element of consecutive sub-range of n equal items.
 *            'last' if no consecutive sub-range of n equal items found. In case of
 *            'n == 0 || n == 1' 'first' is returned.
 */
template <class Iter>
inline Iter consecutive_find(Iter first, Iter last, std::size_t n) {
    std::size_t count(1);
    Iter marker, lead;

    for (marker = lead = first; lead != last; marker = lead, count = 1) {
        for (lead = std::next(marker); (lead != last) && (*marker == *lead); ++count, ++lead)
            ;

        if (count >= n) {
            return marker;
        }
    }
    return marker;
}
}  // namespace base
