/**
 * @author     Andreas Evers
 *
 * @copyright  Copyright © 2021 Andreas Evers
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
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <iomanip>
#include <ios>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

namespace base {

enum class HexStringCapitalization {
    LowerCase,  // b00b13
    UpperCase   // B00B13
};

enum class HexStringFormat {
    NoPrefix_NoComma_NoGap,  // b00b13
    NoPrefix_NoComma,        // b0 0b 13
    NoPrefix_Comma,          // b0, 0b, 13
    Prefix_NoComma,          // 0xb0 0x0b 0x13
    Prefix_Comma,            // 0xb0, 0x0b, 0x13
    Suffix_NoComma,          // b0h 0bh 13h
    Suffix_Comma             // b0h, 0bh, 13h
};

/**
 * @brief Converts your byte (uint8_t) container to a hexadecimal string with various formats
 *
 * See the corresponding unit-tests for the various formats supported by this function.
 *
 * @tparam T container with items of type uint8_t. Must support ranged-for loop access and size()
 * @param cont        Byte container with bytes to convert
 * @param format      Wanted HexString format. See HexStringFormat for format options (default: No Prefix, no comma, no
 * gap)
 * @param cap         Wanted capitalization of hex values (a-f or A-F) (default: LowerCase)
 * @param bytegroup   How many bytes shall be grouped to one hex value (default: 1)
 * @return std::string  HexString
 */
template <typename T>
std::string bytes_2_hexstring(const T& cont, HexStringFormat format = HexStringFormat::NoPrefix_NoComma_NoGap,
                              HexStringCapitalization cap = HexStringCapitalization::LowerCase, uint8_t bytegroup = 1) {
    std::stringstream retval;

    assert(bytegroup > 0);
    size_t i = 0;
    bool first = true;
    bool prefix = false;
    bool suffix = false;
    std::string separator;

    if (format != HexStringFormat::NoPrefix_NoComma_NoGap) {
        separator += " ";
    }
    if (format == HexStringFormat::NoPrefix_Comma || format == HexStringFormat::Prefix_Comma ||
        format == HexStringFormat::Suffix_Comma) {
        separator = "," + separator;
    }
    if (format == HexStringFormat::Prefix_Comma || format == HexStringFormat::Prefix_NoComma) {
        prefix = true;
    }
    if (format == HexStringFormat::Suffix_Comma || format == HexStringFormat::Suffix_NoComma) {
        suffix = true;
    }

    for (uint8_t val : cont) {
        if (i % bytegroup == 0) {
            if (!first) {
                retval << separator;
            }

            if (prefix) {
                retval << "0x";
            }
        }

        retval << std::hex << (cap == HexStringCapitalization::UpperCase ? std::uppercase : std::nouppercase)
               << std::setfill('0') << std::setw(2) << (int)val;

        ++i;
        if (suffix && (i % bytegroup == 0 || i == cont.size())) {
            retval << "h";
        }

        first = false;
    }

    return retval.str();
}

template <typename T>
T hexstring_2_bytes(const std::string& str) {
    T ret{};
    std::string stripped;

    for (char c : str) {
        if ((c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F') || (c >= '0' && c <= '9')) {
            stripped.push_back(c);
        };
    }

    return ret;
}

template <typename T>
inline std::enable_if_t<std::is_integral_v<T>, std::vector<uint8_t>> to_byte_vector(T value) {
    std::size_t bytes = sizeof(T);
    std::vector<uint8_t> vec;
    for (int i = bytes - 1; i >= 0; --i) {
        vec.push_back((uint8_t)((value >> (i * 8)) & 0xFF));
    }
    return vec;
}

}  // namespace base