#ifndef _SORTED_FIND_H_
#define _SORTED_FIND_H_

namespace ae {

template <class Iterator, typename Value, class Compare>
Iterator __sorted_find_helper(Iterator from, Iterator to, const Iterator end,
                              const Value& value, Compare comp) {
    // If from points to searched value, return from
    if (!comp(*from, value) && !comp(value, *from))
        return from;
    // If remaining search area is empty return end
    if (from == to)
        return end;

    size_t half_dist = std::distance(from, to) / 2;

    // For small remaining search scope optimize by linear search
    if (half_dist < 5) {
        while (from <= to) {
            if (comp(*from, value)) {
                from += 1;
                continue;
            }
            if (comp(value, *from))
                return end;
            return from;
        }
    }
    // Else search appropriate upper or lower half of remaining search scope
    else if (comp(value, *(from + half_dist)) == true) {
        return __sorted_find_helper(from, from + half_dist, end, value, comp);
    }
    else {
        return __sorted_find_helper(from + half_dist, to, end, value, comp);
    }
    return end; // Never reached code
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
typename Container::const_iterator
sorted_find(const Container& cont, const Value& value, Compare comp) {
    auto begin = cont.cbegin();
    auto end = cont.cend();
    // In case the container is empty or the value is before the first entry
    // or the value is behind the last entry. Directly leave the search
    if (cont.size() == 0 || comp(value, *begin) || comp(*(end - 1), value))
        return end;
    // Otherwise call the recursive helper function
    return __sorted_find_helper(begin, end - 1, end, value, comp);
}
}

#endif //_SORTED_FIND_H_