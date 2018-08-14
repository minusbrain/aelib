#ifndef _HELPERS_H_
#define _HELPERS_H_

#include <map>
#include <memory>
#include <ratio>

namespace ae {
/**
 * \brief Returns the map-entry for provided key or nullptr if key does not
 * exist
 *
 * \param[in] container The map to search
 * \param[in] key       The key to search for in map
 * \return    Either a pointer to the item if key exists or a nullptr
 */
template <class T_key, class T_entry>
T_entry* mapentry_or_null(const std::map<T_key, T_entry*>& container,
                          T_key key) {
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
T_entry*
mapentry_or_null(const std::map<T_key, std::unique_ptr<T_entry>>& container,
                 T_key key) {
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
int constexpr strlen(const char* str) {
    return *str ? 1 + ae::strlen(str + 1) : 0;
}
}

#endif //_HELPERS_H_