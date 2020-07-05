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

#include <map>
#include <memory>
#include <ratio>

namespace base
{
/**
 * \brief Returns the map-entry for provided key or nullptr if key does not
 * exist
 *
 * \param[in] container The map to search
 * \param[in] key       The key to search for in map
 * \return    Either a pointer to the item if key exists or a nullptr
 */
template <class T_key, class T_entry>
T_entry* mapentry_or_null(const std::map<T_key, T_entry*>& container, T_key key)
{
    auto ret = container.find(key);
    return (ret == container.end()) ? nullptr : ret->second;
}

/**
 * \brief Returns the map-entry for provided key or nullptr if key does not
 * exist
 *
 * \param[in] container The map to search
 * \param[in] key       The key to search for in map
 * \return    Either a pointer to the item if key exists or a nullptr
 */
template <class T_key, class T_entry>
T_entry* mapentry_or_null(const std::map<T_key, std::unique_ptr<T_entry>>& container,
                          T_key key)
{
    auto ret = container.find(key);
    return (ret == container.end()) ? nullptr : ret->second.get();
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
int constexpr strlen(const char* str) { return *str ? 1 + base::strlen(str + 1) : 0; }
}  // namespace base
