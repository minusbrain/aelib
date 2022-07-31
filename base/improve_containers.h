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
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <vector>

namespace base {
template <typename T>
inline std::ostream& stream_out_plain_object(T obj, std::ostream& os) {
    os << obj;
    return os;
}

template <>
inline std::ostream& stream_out_plain_object<uint8_t>(uint8_t obj, std::ostream& os) {
    os << "0x" << std::hex << std::setfill('0') << std::setw(2) << obj;
    return os;
}

/**
 * @brief      ostream operator to stream out vectors of any type
 *
 * This streams out the content of the provided vector to the provided
 * ostream. Only limitation is there must also be an operator implementation
 * to stream out a single element of T.
 *
 * Example Usage:
 * @code{.cpp}
 * std::vector<std::string> vec{"hello", "world"};
 *
 * std::cout << vec;
 * @endcode
 *
 * @param      os         The output stream
 * @param[in]  container  The container to stream out
 *
 * @tparam     T       The element type of the vector
 *
 * @return     The updated output stream
 */
template <typename T>
inline std::ostream& stream_out_plain_container(char const* str, std::ostream& os, const T& container) {
    bool skip = true;
    os << str << " {";
    for (auto& x : container) {
        if (skip) {
            skip = false;
        } else {
            os << ", ";
        }

        stream_out_plain_object(x, os);
    }
    os << "}";
    return os;
}

inline std::vector<std::string> tokenize(const std::string& input, char seperator) {
    std::stringstream inputstream(input);
    std::string token;
    std::vector<std::string> tokens;

    while (getline(inputstream, token, seperator)) {
        tokens.push_back(token);
    }
    return tokens;
}

template <class T>
inline std::vector<T>& push_back(std::vector<T>& target, const std::vector<T>& to_push) {
    target.insert(target.end(), to_push.begin(), to_push.end());
    return target;
}

}  // namespace base

namespace std {
template <typename T, size_t size>
inline std::ostream& operator<<(std::ostream& os, const std::array<T, size>& arr) {
    return base::stream_out_plain_container<std::array<T, size>>("Array", os, arr);
}

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    return base::stream_out_plain_container<std::vector<T>>("Vector", os, vec);
}

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const std::list<T>& list) {
    return base::stream_out_plain_container<std::list<T>>("List", os, list);
}

template <typename Key, typename Val>
inline std::ostream& operator<<(std::ostream& os, const std::map<Key, Val>& map) {
    bool skip = true;
    os << "Map {";
    for (auto& x : map) {
        if (skip) {
            skip = false;
        } else {
            os << ", ";
        }
        os << "{" << x.first << " -> " << x.second << "}";
    }
    os << "}";
    return os;
}
}  // namespace std
namespace base {
template <typename T>
void sort(T& container) {
    std::sort(container.begin(), container.end());
}

template <typename T, size_t len>
void sort(T* container) {
    std::sort(container, container + len);
}

template <typename X>
void sort(std::list<X>& container) {
    container.sort();
}

template <typename T, class Compare>
void sort(T& container, Compare comp) {
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
    return std::count_if(container.cbegin(), container.cend(), pred);
}

template <class T, class UnaryPredicate>
typename T::iterator remove_if(T& container, UnaryPredicate pred) {
    return std::remove_if(container.begin(), container.end(), pred);
}

template <class T, class U>
auto copy(T& destination, U& source) {
    return std::copy(source.begin(), source.end(), std::back_inserter(destination));
}

template <class T, class U>
typename T::iterator find(T& container, const U& value) {
    return std::find(container.begin(), container.end(), value);
}

template <class T, class UnaryPredicate>
typename T::iterator find_if(T& container, UnaryPredicate pred) {
    return std::find_if(container.begin(), container.end(), pred);
}

template <class T, class U>
typename T::const_iterator find(const T& container, const U& value) {
    return std::find(container.cbegin(), container.cend(), value);
}

template <class T, class UnaryPredicate>
typename T::const_iterator find_if(const T& container, UnaryPredicate pred) {
    return std::find_if(container.cbegin(), container.cend(), pred);
}

template <class T>
typename T::iterator adjacent_find(T& container) {
    return std::adjacent_find(container.begin(), container.end());
}

template <class T>
typename T::const_iterator adjacent_find(const T& container) {
    return std::adjacent_find(container.cbegin(), container.cend());
}

template <class T, class UnaryFunction>
UnaryFunction for_each(T& container, UnaryFunction func) {
    return std::for_each(container.begin(), container.end(), func);
}
}  // namespace base
