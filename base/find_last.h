#pragma once

namespace ae
{
    /**
    * \brief Find the last occurrence of value in range
    *
    * This algorithm searches a given range for a given value and returns
    * an iterator to the last occurence of it.
    * Consider the following code snippet
    * \code
    *     std::vector<int> values = { 5, 13, 5, 22, 5, 7 };
    *     auto it = find_last(values.begin(), values.end(), 5);
    * \endcode
    * The returned iterator 'it' now points to the last occurrence of '5' in the vector
    *
    * \param[in] begin  Iterator indicating the beginning of the range to search
    * \param[in] end    Iterator indicating the end of the range to search
    * \param[in] val    Value to search for
    * \return    Iterator to the last occuring element equal to 'val'. If 'val' does not
    *            occur in range 'end' is returned.
    */
    template <class Iter, class T>
    Iter find_last(Iter begin, Iter end, const T& val)
    {
        Iter last(end);
        Iter current(begin);

        while (current != end) {
            if (*current == val) {
                last = current;
            }
            ++current;
        }

        return last;
    }
}
