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
#include <base/conversion.h>

#include "gtest/gtest.h"

TEST(Conversion, bytes_2_hexstring_lower_case_1byte_group_various_formats_using_vector) {
    EXPECT_EQ(std::string("00010f1011a0a1ff"),
              base::bytes_2_hexstring(std::vector<uint8_t>{0, 1, 15, 16, 17, 160, 161, 255}));
    EXPECT_EQ(std::string("00010f1011a0a1ff"),
              base::bytes_2_hexstring(std::vector<uint8_t>{0, 1, 15, 16, 17, 160, 161, 255},
                                      base::HexStringFormat::NoPrefix_NoComma_NoGap));
    EXPECT_EQ(std::string("0a0b0c0d0e0fa0b0c0d0e0f0"),
              base::bytes_2_hexstring(std::vector<uint8_t>{10, 11, 12, 13, 14, 15, 160, 176, 192, 208, 224, 240},
                                      base::HexStringFormat::NoPrefix_NoComma_NoGap,
                                      base::HexStringCapitalization::LowerCase));
    EXPECT_EQ(std::string("00 01 0f 10 11 a0 a1 ff"),
              base::bytes_2_hexstring(std::vector<uint8_t>{0, 1, 15, 16, 17, 160, 161, 255},
                                      base::HexStringFormat::NoPrefix_NoComma));
    EXPECT_EQ(std::string("00, 01, 0f, 10, 11, a0, a1, ff"),
              base::bytes_2_hexstring(std::vector<uint8_t>{0, 1, 15, 16, 17, 160, 161, 255},
                                      base::HexStringFormat::NoPrefix_Comma));
    EXPECT_EQ(std::string("0x00 0x01 0x0f 0x10 0x11 0xa0 0xa1 0xff"),
              base::bytes_2_hexstring(std::vector<uint8_t>{0, 1, 15, 16, 17, 160, 161, 255},
                                      base::HexStringFormat::Prefix_NoComma));
    EXPECT_EQ(std::string("0x00, 0x01, 0x0f, 0x10, 0x11, 0xa0, 0xa1, 0xff"),
              base::bytes_2_hexstring(std::vector<uint8_t>{0, 1, 15, 16, 17, 160, 161, 255},
                                      base::HexStringFormat::Prefix_Comma));
    EXPECT_EQ(std::string("00h 01h 0fh 10h 11h a0h a1h ffh"),
              base::bytes_2_hexstring(std::vector<uint8_t>{0, 1, 15, 16, 17, 160, 161, 255},
                                      base::HexStringFormat::Suffix_NoComma));
    EXPECT_EQ(std::string("00h, 01h, 0fh, 10h, 11h, a0h, a1h, ffh"),
              base::bytes_2_hexstring(std::vector<uint8_t>{0, 1, 15, 16, 17, 160, 161, 255},
                                      base::HexStringFormat::Suffix_Comma));
}

TEST(Conversion, bytes_2_hexstring_upper_case_1byte_group_various_formats_using_vector) {
    EXPECT_EQ(std::string("00010F1011A0A1FF"),
              base::bytes_2_hexstring(std::vector<uint8_t>{0, 1, 15, 16, 17, 160, 161, 255},
                                      base::HexStringFormat::NoPrefix_NoComma_NoGap,
                                      base::HexStringCapitalization::UpperCase));
    EXPECT_EQ(std::string("0A0B0C0D0E0FA0B0C0D0E0F0"),
              base::bytes_2_hexstring(std::vector<uint8_t>{10, 11, 12, 13, 14, 15, 160, 176, 192, 208, 224, 240},
                                      base::HexStringFormat::NoPrefix_NoComma_NoGap,
                                      base::HexStringCapitalization::UpperCase));
    EXPECT_EQ(
        std::string("00 01 0F 10 11 A0 A1 FF"),
        base::bytes_2_hexstring(std::vector<uint8_t>{0, 1, 15, 16, 17, 160, 161, 255},
                                base::HexStringFormat::NoPrefix_NoComma, base::HexStringCapitalization::UpperCase));
    EXPECT_EQ(std::string("00, 01, 0F, 10, 11, A0, A1, FF"),
              base::bytes_2_hexstring(std::vector<uint8_t>{0, 1, 15, 16, 17, 160, 161, 255},
                                      base::HexStringFormat::NoPrefix_Comma, base::HexStringCapitalization::UpperCase));
    EXPECT_EQ(std::string("0x00 0x01 0x0F 0x10 0x11 0xA0 0xA1 0xFF"),
              base::bytes_2_hexstring(std::vector<uint8_t>{0, 1, 15, 16, 17, 160, 161, 255},
                                      base::HexStringFormat::Prefix_NoComma, base::HexStringCapitalization::UpperCase));
    EXPECT_EQ(std::string("0x00, 0x01, 0x0F, 0x10, 0x11, 0xA0, 0xA1, 0xFF"),
              base::bytes_2_hexstring(std::vector<uint8_t>{0, 1, 15, 16, 17, 160, 161, 255},
                                      base::HexStringFormat::Prefix_Comma, base::HexStringCapitalization::UpperCase));
    EXPECT_EQ(std::string("00h 01h 0Fh 10h 11h A0h A1h FFh"),
              base::bytes_2_hexstring(std::vector<uint8_t>{0, 1, 15, 16, 17, 160, 161, 255},
                                      base::HexStringFormat::Suffix_NoComma, base::HexStringCapitalization::UpperCase));
    EXPECT_EQ(std::string("00h, 01h, 0Fh, 10h, 11h, A0h, A1h, FFh"),
              base::bytes_2_hexstring(std::vector<uint8_t>{0, 1, 15, 16, 17, 160, 161, 255},
                                      base::HexStringFormat::Suffix_Comma, base::HexStringCapitalization::UpperCase));
}

TEST(Conversion, bytes_2_hexstring_upper_case_2byte_group_various_formats_using_vector) {
    EXPECT_EQ(std::string("00010F1011A0A1FF"),
              base::bytes_2_hexstring(std::vector<uint8_t>{0, 1, 15, 16, 17, 160, 161, 255},
                                      base::HexStringFormat::NoPrefix_NoComma_NoGap,
                                      base::HexStringCapitalization::UpperCase, 2));
    EXPECT_EQ(std::string("0A0B0C0D0E0FA0B0C0D0E0F0"),
              base::bytes_2_hexstring(std::vector<uint8_t>{10, 11, 12, 13, 14, 15, 160, 176, 192, 208, 224, 240},
                                      base::HexStringFormat::NoPrefix_NoComma_NoGap,
                                      base::HexStringCapitalization::UpperCase, 2));
    EXPECT_EQ(
        std::string("0001 0F10 11A0 A1FF"),
        base::bytes_2_hexstring(std::vector<uint8_t>{0, 1, 15, 16, 17, 160, 161, 255},
                                base::HexStringFormat::NoPrefix_NoComma, base::HexStringCapitalization::UpperCase, 2));
    EXPECT_EQ(
        std::string("0001, 0F10, 11A0, A1FF"),
        base::bytes_2_hexstring(std::vector<uint8_t>{0, 1, 15, 16, 17, 160, 161, 255},
                                base::HexStringFormat::NoPrefix_Comma, base::HexStringCapitalization::UpperCase, 2));
    EXPECT_EQ(
        std::string("0x0001 0x0F10 0x11A0 0xA1FF"),
        base::bytes_2_hexstring(std::vector<uint8_t>{0, 1, 15, 16, 17, 160, 161, 255},
                                base::HexStringFormat::Prefix_NoComma, base::HexStringCapitalization::UpperCase, 2));
    EXPECT_EQ(
        std::string("0x0001, 0x0F10, 0x11A0, 0xA1FF"),
        base::bytes_2_hexstring(std::vector<uint8_t>{0, 1, 15, 16, 17, 160, 161, 255},
                                base::HexStringFormat::Prefix_Comma, base::HexStringCapitalization::UpperCase, 2));
    EXPECT_EQ(
        std::string("0001h 0F10h 11A0h A1FFh"),
        base::bytes_2_hexstring(std::vector<uint8_t>{0, 1, 15, 16, 17, 160, 161, 255},
                                base::HexStringFormat::Suffix_NoComma, base::HexStringCapitalization::UpperCase, 2));
    EXPECT_EQ(
        std::string("0001h, 0F10h, 11A0h, A1FFh"),
        base::bytes_2_hexstring(std::vector<uint8_t>{0, 1, 15, 16, 17, 160, 161, 255},
                                base::HexStringFormat::Suffix_Comma, base::HexStringCapitalization::UpperCase, 2));
}

TEST(Conversion, bytes_2_hexstring_upper_case_4byte_group_various_formats_using_vector) {
    EXPECT_EQ(std::string("00010F1011A0A1FF"),
              base::bytes_2_hexstring(std::vector<uint8_t>{0, 1, 15, 16, 17, 160, 161, 255},
                                      base::HexStringFormat::NoPrefix_NoComma_NoGap,
                                      base::HexStringCapitalization::UpperCase, 4));
    EXPECT_EQ(std::string("0A0B0C0D0E0FA0B0C0D0E0F0"),
              base::bytes_2_hexstring(std::vector<uint8_t>{10, 11, 12, 13, 14, 15, 160, 176, 192, 208, 224, 240},
                                      base::HexStringFormat::NoPrefix_NoComma_NoGap,
                                      base::HexStringCapitalization::UpperCase, 4));
    EXPECT_EQ(
        std::string("00010F10 11A0A1FF"),
        base::bytes_2_hexstring(std::vector<uint8_t>{0, 1, 15, 16, 17, 160, 161, 255},
                                base::HexStringFormat::NoPrefix_NoComma, base::HexStringCapitalization::UpperCase, 4));
    EXPECT_EQ(
        std::string("00010F10, 11A0A1FF"),
        base::bytes_2_hexstring(std::vector<uint8_t>{0, 1, 15, 16, 17, 160, 161, 255},
                                base::HexStringFormat::NoPrefix_Comma, base::HexStringCapitalization::UpperCase, 4));
    EXPECT_EQ(
        std::string("0x00010F10 0x11A0A1FF"),
        base::bytes_2_hexstring(std::vector<uint8_t>{0, 1, 15, 16, 17, 160, 161, 255},
                                base::HexStringFormat::Prefix_NoComma, base::HexStringCapitalization::UpperCase, 4));
    EXPECT_EQ(
        std::string("0x00010F10, 0x11A0A1FF"),
        base::bytes_2_hexstring(std::vector<uint8_t>{0, 1, 15, 16, 17, 160, 161, 255},
                                base::HexStringFormat::Prefix_Comma, base::HexStringCapitalization::UpperCase, 4));
    EXPECT_EQ(
        std::string("00010F10h 11A0A1FFh"),
        base::bytes_2_hexstring(std::vector<uint8_t>{0, 1, 15, 16, 17, 160, 161, 255},
                                base::HexStringFormat::Suffix_NoComma, base::HexStringCapitalization::UpperCase, 4));
    EXPECT_EQ(
        std::string("00010F10h, 11A0A1FFh"),
        base::bytes_2_hexstring(std::vector<uint8_t>{0, 1, 15, 16, 17, 160, 161, 255},
                                base::HexStringFormat::Suffix_Comma, base::HexStringCapitalization::UpperCase, 4));
}

TEST(Conversion, bytes_2_hexstring_upper_case_4byte_group_various_formats_using_vector_with_odd_number_of_bytes) {
    EXPECT_EQ(std::string("00010F1011A0A1FF01"),
              base::bytes_2_hexstring(std::vector<uint8_t>{0, 1, 15, 16, 17, 160, 161, 255, 1},
                                      base::HexStringFormat::NoPrefix_NoComma_NoGap,
                                      base::HexStringCapitalization::UpperCase, 4));
    EXPECT_EQ(std::string("0A0B0C0D0E0FA0B0C0D0E0F001"),
              base::bytes_2_hexstring(std::vector<uint8_t>{10, 11, 12, 13, 14, 15, 160, 176, 192, 208, 224, 240, 1},
                                      base::HexStringFormat::NoPrefix_NoComma_NoGap,
                                      base::HexStringCapitalization::UpperCase, 4));
    EXPECT_EQ(
        std::string("00010F10 11A0A1FF 01"),
        base::bytes_2_hexstring(std::vector<uint8_t>{0, 1, 15, 16, 17, 160, 161, 255, 1},
                                base::HexStringFormat::NoPrefix_NoComma, base::HexStringCapitalization::UpperCase, 4));
    EXPECT_EQ(
        std::string("00010F10, 11A0A1FF, 01"),
        base::bytes_2_hexstring(std::vector<uint8_t>{0, 1, 15, 16, 17, 160, 161, 255, 1},
                                base::HexStringFormat::NoPrefix_Comma, base::HexStringCapitalization::UpperCase, 4));
    EXPECT_EQ(
        std::string("0x00010F10 0x11A0A1FF 0x01"),
        base::bytes_2_hexstring(std::vector<uint8_t>{0, 1, 15, 16, 17, 160, 161, 255, 1},
                                base::HexStringFormat::Prefix_NoComma, base::HexStringCapitalization::UpperCase, 4));
    EXPECT_EQ(
        std::string("0x00010F10, 0x11A0A1FF, 0x01"),
        base::bytes_2_hexstring(std::vector<uint8_t>{0, 1, 15, 16, 17, 160, 161, 255, 1},
                                base::HexStringFormat::Prefix_Comma, base::HexStringCapitalization::UpperCase, 4));
    EXPECT_EQ(
        std::string("00010F10h 11A0A1FFh 01h"),
        base::bytes_2_hexstring(std::vector<uint8_t>{0, 1, 15, 16, 17, 160, 161, 255, 1},
                                base::HexStringFormat::Suffix_NoComma, base::HexStringCapitalization::UpperCase, 4));
    EXPECT_EQ(
        std::string("00010F10h, 11A0A1FFh, 01h"),
        base::bytes_2_hexstring(std::vector<uint8_t>{0, 1, 15, 16, 17, 160, 161, 255, 1},
                                base::HexStringFormat::Suffix_Comma, base::HexStringCapitalization::UpperCase, 4));

    EXPECT_EQ(
        std::string("00010F10 11A0A1FF 0102"),
        base::bytes_2_hexstring(std::vector<uint8_t>{0, 1, 15, 16, 17, 160, 161, 255, 1, 2},
                                base::HexStringFormat::NoPrefix_NoComma, base::HexStringCapitalization::UpperCase, 4));
    EXPECT_EQ(
        std::string("00010F10, 11A0A1FF, 0102"),
        base::bytes_2_hexstring(std::vector<uint8_t>{0, 1, 15, 16, 17, 160, 161, 255, 1, 2},
                                base::HexStringFormat::NoPrefix_Comma, base::HexStringCapitalization::UpperCase, 4));
    EXPECT_EQ(
        std::string("0x00010F10 0x11A0A1FF 0x0102"),
        base::bytes_2_hexstring(std::vector<uint8_t>{0, 1, 15, 16, 17, 160, 161, 255, 1, 2},
                                base::HexStringFormat::Prefix_NoComma, base::HexStringCapitalization::UpperCase, 4));
    EXPECT_EQ(
        std::string("0x00010F10, 0x11A0A1FF, 0x0102"),
        base::bytes_2_hexstring(std::vector<uint8_t>{0, 1, 15, 16, 17, 160, 161, 255, 1, 2},
                                base::HexStringFormat::Prefix_Comma, base::HexStringCapitalization::UpperCase, 4));
    EXPECT_EQ(
        std::string("00010F10h 11A0A1FFh 0102h"),
        base::bytes_2_hexstring(std::vector<uint8_t>{0, 1, 15, 16, 17, 160, 161, 255, 1, 2},
                                base::HexStringFormat::Suffix_NoComma, base::HexStringCapitalization::UpperCase, 4));
    EXPECT_EQ(
        std::string("00010F10h, 11A0A1FFh, 0102h"),
        base::bytes_2_hexstring(std::vector<uint8_t>{0, 1, 15, 16, 17, 160, 161, 255, 1, 2},
                                base::HexStringFormat::Suffix_Comma, base::HexStringCapitalization::UpperCase, 4));

    EXPECT_EQ(
        std::string("00010F10 11A0A1FF 010203"),
        base::bytes_2_hexstring(std::vector<uint8_t>{0, 1, 15, 16, 17, 160, 161, 255, 1, 2, 3},
                                base::HexStringFormat::NoPrefix_NoComma, base::HexStringCapitalization::UpperCase, 4));
    EXPECT_EQ(
        std::string("00010F10, 11A0A1FF, 010203"),
        base::bytes_2_hexstring(std::vector<uint8_t>{0, 1, 15, 16, 17, 160, 161, 255, 1, 2, 3},
                                base::HexStringFormat::NoPrefix_Comma, base::HexStringCapitalization::UpperCase, 4));
    EXPECT_EQ(
        std::string("0x00010F10 0x11A0A1FF 0x010203"),
        base::bytes_2_hexstring(std::vector<uint8_t>{0, 1, 15, 16, 17, 160, 161, 255, 1, 2, 3},
                                base::HexStringFormat::Prefix_NoComma, base::HexStringCapitalization::UpperCase, 4));
    EXPECT_EQ(
        std::string("0x00010F10, 0x11A0A1FF, 0x010203"),
        base::bytes_2_hexstring(std::vector<uint8_t>{0, 1, 15, 16, 17, 160, 161, 255, 1, 2, 3},
                                base::HexStringFormat::Prefix_Comma, base::HexStringCapitalization::UpperCase, 4));
    EXPECT_EQ(
        std::string("00010F10h 11A0A1FFh 010203h"),
        base::bytes_2_hexstring(std::vector<uint8_t>{0, 1, 15, 16, 17, 160, 161, 255, 1, 2, 3},
                                base::HexStringFormat::Suffix_NoComma, base::HexStringCapitalization::UpperCase, 4));
    EXPECT_EQ(
        std::string("00010F10h, 11A0A1FFh, 010203h"),
        base::bytes_2_hexstring(std::vector<uint8_t>{0, 1, 15, 16, 17, 160, 161, 255, 1, 2, 3},
                                base::HexStringFormat::Suffix_Comma, base::HexStringCapitalization::UpperCase, 4));
}

TEST(Conversion, bytes_2_hexstring_upper_case_4byte_group_various_formats_using_empty_vector) {
    EXPECT_EQ(std::string(""),
              base::bytes_2_hexstring(std::vector<uint8_t>{}, base::HexStringFormat::NoPrefix_NoComma_NoGap,
                                      base::HexStringCapitalization::UpperCase, 4));
    EXPECT_EQ(std::string(""), base::bytes_2_hexstring(std::vector<uint8_t>{}, base::HexStringFormat::NoPrefix_NoComma,
                                                       base::HexStringCapitalization::UpperCase, 4));
    EXPECT_EQ(std::string(""), base::bytes_2_hexstring(std::vector<uint8_t>{}, base::HexStringFormat::NoPrefix_Comma,
                                                       base::HexStringCapitalization::UpperCase, 4));
    EXPECT_EQ(std::string(""), base::bytes_2_hexstring(std::vector<uint8_t>{}, base::HexStringFormat::Prefix_NoComma,
                                                       base::HexStringCapitalization::UpperCase, 4));
    EXPECT_EQ(std::string(""), base::bytes_2_hexstring(std::vector<uint8_t>{}, base::HexStringFormat::Prefix_Comma,
                                                       base::HexStringCapitalization::UpperCase, 4));
    EXPECT_EQ(std::string(""), base::bytes_2_hexstring(std::vector<uint8_t>{}, base::HexStringFormat::Suffix_NoComma,
                                                       base::HexStringCapitalization::UpperCase, 4));
    EXPECT_EQ(std::string(""), base::bytes_2_hexstring(std::vector<uint8_t>{}, base::HexStringFormat::Suffix_Comma,
                                                       base::HexStringCapitalization::UpperCase, 4));
}
/*
TEST(Conversion, hexstring_2_bytes) {
    EXPECT_EQ(std::string("abcdefABCDEF1234567890"),
              base::hexstring_2_bytes(std::string("abcdefghijklmnopqrstuvw_/|ABCDEFGHIJKLMNOPQRSTUVW1234567890-")));
}
*/