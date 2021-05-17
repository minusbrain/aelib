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

namespace base {
/**
 * \brief Find the last occurrence of value in range
 *
 * This algorithm searches a given range for a given value and returns
 * an iterator to the last occurence of it.
 *
 * Consider the following code snippet
 * \code
 *     std::vector<int> values = { 5, 13, 5, 22, 5, 7 };
 *     auto it = find_last(values.begin(), values.end(), 5);
 * \endcode
 * The returned iterator 'it' now points to the last occurrence of '5' in the vector
 *
 * \param[in] first  Iterator indicating the beginning of the range to search
 * \param[in] last   Iterator indicating the end of the range to search
 * \param[in] val    Value to search for
 * \return    Iterator to the last occuring element equal to 'val'. If 'val' does not
 *            occur in range 'last' is returned.
 */
template <class Iter, class T>
inline Iter find_last(Iter first, Iter last, const T& val) {
    Iter lastfound(last);
    Iter current(first);

    while (current != last) {
        if (*current == val) {
            lastfound = current;
        }
        ++current;
    }

    return lastfound;
}
}  // namespace base
