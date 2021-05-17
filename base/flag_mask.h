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
#include <initializer_list>
#include <limits>
#include <type_traits>

namespace base {
/**
 * \brief Flagmask for arbritary integer-based types (integers, enums, enum class, ....)
 *
 * Example use case
 *
 * \code
 *      enum class MyEnum : uint32_t
 *      {
 *          a = 0x01,
 *          b = 0x02,
 *          c = 0x80000000
 *      };
 *
 *      base::flag_mask<MyEnum> mask;
        mask.set(MyEnum::a).set(MyEnum::c);

        if(mask.check(MyEnum::b)) {
            ...
        }
 * \endcode
 */
template <typename FLAG>
class flag_mask {
   public:
    using BASETYPE = typename std::underlying_type<FLAG>::type;
    /**
     * @brief      Instantiate flagmask with initial
     *
     * @param[in]  init  The initial raw flagmask value
     */
    flag_mask(const BASETYPE init) : value(init) {}

    /**
     * @brief      Instantiate flagmask with all bits off
     */
    flag_mask() : value(0) {}

    /**
     * @brief      Set single flag
     *
     * @param[in]  flag  The flag to set
     *
     * @return     Reference to this flagmask, can be used to chain calls to set, unset,
     *             clear, ...
     */
    flag_mask& set(const FLAG flag) {
        value |= (BASETYPE)flag;
        return *this;
    }

    /**
     * @brief      Set all flags
     *
     * @return     Reference to this flagmask, can be used to chain calls to set, unset,
     *             clear, ...
     */
    flag_mask& set_all() {
        value = std::numeric_limits<BASETYPE>::max();
        return *this;
    }

    /**
     * @brief      Unset single flag
     *
     * @param[in]  flag  The flag to unset / clear
     *
     * @return     Reference to this flagmask, can be used to chain calls to set, unset,
     *             clear, ...
     */
    flag_mask& unset(const FLAG flag) {
        value &= ~((BASETYPE)flag);
        return *this;
    }

    /**
     * @brief      Clear all flags
     *
     * @return     Reference to this flagmask, can be used to chain calls to set, unset,
     *             clear, ...
     */
    flag_mask& clear() {
        value = 0;
        return *this;
    }

    /**
     * @brief      Check if provided flag is set or not
     *
     * @param[in]  flag  The flag to check
     *
     * @return     true if flag is set, false if not
     */
    bool check(const FLAG flag) { return value & (BASETYPE)flag; }

    /**
     * @brief      Check if all provided flags are set or not
     *
     * @param[in]  flags  List of flags to check
     *
     * @return     true if all flags are set, false if one or more are not checked
     */
    bool check_all(std::initializer_list<const FLAG> flags) {
        for (auto flag : flags) {
            if (check(flag) == false) {
                return false;
            }
        }
        return true;
    }

    /**
     * @brief      Get the read-only internal flagmask value
     *
     * @return     Flagmask value
     */
    BASETYPE raw_get() { return value; }

    /**
     * @brief      Set the internal flagmask value
     *
     * @param[in]  newvalue  The new value to set the flagmask to
     */
    void raw_set(const BASETYPE newvalue) { value = newvalue; }

   private:
    BASETYPE value;
};
}  // namespace base
