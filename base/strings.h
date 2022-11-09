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
#include <string>

#include "improve_containers.h"

namespace base {

// trim from start (in place)
inline void ltrim_inplace(std::string& s) {
    s.erase(s.begin(), find_if(s, [](unsigned char ch) { return !std::isspace(ch); }));
}

// trim from end (in place)
inline void rtrim_inplace(std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(), s.end());
}

// trim from both ends (in place)
inline void trim_inplace(std::string& s) {
    ltrim_inplace(s);
    rtrim_inplace(s);
}

// transform to upper (in place)
inline void toupper_inplace(std::string& s) {
    std::for_each(s.begin(), s.end(), [](char& c) { c = std::toupper(c, std::locale()); });
}

// transform to lower (in place)
inline void tolower_inplace(std::string& s) {
    std::for_each(s.begin(), s.end(), [](char& c) { c = std::tolower(c, std::locale()); });
}

// transform to upper
inline std::string toupper(const std::string& in) {
    std::string s(in);
    std::for_each(s.begin(), s.end(), [](char& c) { c = std::toupper(c, std::locale()); });
    return s;
}

// transform to lower
inline std::string tolower(const std::string& in) {
    std::string s(in);
    std::for_each(s.begin(), s.end(), [](char& c) { c = std::tolower(c, std::locale()); });
    return s;
}

// replace all chars (in place)
inline void replace_all_inplace(std::string& s, const char search, const char replace) {
    std::for_each(s.begin(), s.end(), [&](char& c) {
        if (c == search) c = replace;
    });
}

inline std::vector<std::string> split(const std::string& input, char sep) {
    std::istringstream ss(input);
    std::string token;
    std::vector<std::string> returnVector;

    while (std::getline(ss, token, sep)) {
        returnVector.push_back(token);
    }

    return returnVector;
}

inline std::vector<std::string> split(const std::string& input, const std::vector<char>& seps) {
    std::vector<std::string> retval;
    auto it_last = input.begin();
    auto is_separator = [&seps](char sep) { return base::find(seps, sep) != seps.end(); };
    auto it_sep = std::find_if(input.begin(), input.end(), is_separator);
    while (it_sep != input.end()) {
        retval.emplace_back(it_last, it_sep);
        it_last = it_sep + 1;
        while (is_separator(*it_last)) ++it_last;  // Skip multiple subsequent separators
        it_sep = std::find_if(it_last, input.end(), is_separator);
    };
    retval.emplace_back(it_last, it_sep);
    return retval;
}

/**
 * \brief Compile-time strlen for C-type strings
 * Returns the length of the string in bytes of the provided C-type string.
 * Allows for usage of strlen in contexts where the value is required at
 * compile-time
 *
 * \param[in] str C-style string null-terminated to calculate the length of
 * \return    Length in bytes
 */
int constexpr strlen_ce(const char* str) { return *str ? 1 + base::strlen_ce(str + 1) : 0; }

}  // namespace base