#ifndef _IMPROVE_CONTAINERS_H_
#define _IMPROVE_CONTAINERS_H_

#include <algorithm>
#include <iostream>
#include <list>
#include <map>
#include <vector>

namespace ae {
template <typename T>
std::ostream& stream_out_plain_container(char const* str, std::ostream& os,
                                         const T& container) {
    bool skip = true;
    os << str << " {";
    for (auto& x : container) {
        if (skip) {
            skip = false;
        }
        else {
            os << ", ";
        }
        os << x;
    }
    os << "}";
    return os;
}
}

template <typename T, size_t size>
std::ostream& operator<<(std::ostream& os, const std::array<T, size>& vec) {
    return ae::stream_out_plain_container<std::array<T, size>>("Array", os,
                                                               vec);
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    return ae::stream_out_plain_container<std::vector<T>>("Vector", os, vec);
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::list<T>& list) {
    return ae::stream_out_plain_container<std::list<T>>("List", os, list);
}

template <typename Key, typename Val>
std::ostream& operator<<(std::ostream& os, const std::map<Key, Val>& map) {
    bool skip = true;
    os << "Map {";
    for (auto& x : map) {
        if (skip) {
            skip = false;
        }
        else {
            os << ", ";
        }
        os << "{" << x.first << " -> " << x.second << "}";
    }
    os << "}";
    return os;
}

namespace ae {
template <typename T> void sort(T& container) {
    std::sort(container.begin(), container.end());
}

template <typename T, size_t len> void sort(T* container) {
    std::sort(container, container + len);
}

template <typename X> void sort(std::list<X>& container) { container.sort(); }

template <typename T, class Compare> void sort(T& container, Compare comp) {
    std::sort(container.begin(), container.end(), comp);
}

template <typename T, size_t len, class Compare>
void sort(T* container, Compare comp) {
    std::sort(container, container + len, comp);
}

template <typename X, class Compare>
void sort(std::list<X>& container, Compare comp) {
    container.sort(comp);
}

template <class T, class UnaryPredicate>
int count_if(T& container, UnaryPredicate pred) {
    return count_if(container.begin(), container.end(), pred);
}

template <class T, class UnaryPredicate>
typename T::iterator remove_if(T& container, UnaryPredicate pred) {
    return remove_if(container.begin(), container.end(), pred);
}

template <class T, class UnaryPredicate>
typename T::iterator find_if(T& container, UnaryPredicate pred) {
    return find_if(container.begin(), container.end(), pred);
}

template <class T, class UnaryFunction>
UnaryFunction for_each(T& container, UnaryFunction func) {
    return for_each(container.begin(), container.end(), func);
}
}

#endif //_IMPROVE_CONTAINERS_H_