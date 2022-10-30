/**
 * @author     Andreas Evers
 *
 * @copyright  Copyright © 2020-present Andreas Evers
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
#include <base/strings.h>

#include "gtest/gtest.h"

TEST(Strings, LeftTrimInPlace_StringWithoutLeadingWhitespaces_NoChange) {
    std::string str = "Foo Bar   ";
    std::string expected = str;
    base::ltrim_inplace(str);
    EXPECT_EQ(expected, str);
}

TEST(Strings, LeftTrimInPlace_StringWithLeadingWhitespaces_LeadingWhitespacesRemoved) {
    std::string str = " \tFoo Bar   ";
    std::string expected = "Foo Bar   ";
    base::ltrim_inplace(str);
    EXPECT_EQ(expected, str);
}

TEST(Strings, RightTrimInPlace_StringWithoutTrailingWhitespaces_NoChange) {
    std::string str = " \tFoo Bar";
    std::string expected = str;
    base::rtrim_inplace(str);
    EXPECT_EQ(expected, str);
}

TEST(Strings, RightTrimInPlace_StringWithTrailingWhitespaces_TrailingWhitespacesRemoved) {
    std::string str = " \tFoo Bar \t  ";
    std::string expected = " \tFoo Bar";
    base::rtrim_inplace(str);
    EXPECT_EQ(expected, str);
}

TEST(Strings, TrimAllInPlace_StringWithNoLeadingOrTrailingWhitespaces_NoChange) {
    std::string str = "Foo \tBar";
    std::string expected = str;
    base::trim_inplace(str);
    EXPECT_EQ(expected, str);
}

TEST(Strings, TrimAllInPlace_StringWithTrailingWhitespaces_RemoveTrailingWhitespaces) {
    std::string str = "Foo \tBar \t ";
    std::string expected = "Foo \tBar";
    base::trim_inplace(str);
    EXPECT_EQ(expected, str);
}

TEST(Strings, TrimAllInPlace_StringWithLeadingWhitespaces_RemoveLeadingWhitespaces) {
    std::string str = " \t Foo \tBar";
    std::string expected = "Foo \tBar";
    base::trim_inplace(str);
    EXPECT_EQ(expected, str);
}

TEST(Strings, TrimAllInPlace_StringWithLeadingAndTrailingWhitespaces_RemoveLeadingAndTrailingWhitespaces) {
    std::string str = " \t Foo \tBar\t \t";
    std::string expected = "Foo \tBar";
    base::trim_inplace(str);
    EXPECT_EQ(expected, str);
}

TEST(Strings, ToUpperInPlace_NormalString_ExpectAllUpper) {
    std::string str = "FooBar";
    std::string expected = "FOOBAR";
    base::toupper_inplace(str);
    EXPECT_EQ(expected, str);
}

TEST(Strings, ToUpperInPlace_StringWithSpecialChars_ExpectAllUpperAndSpecialCharsUntouched) {
    std::string str = "Foo_-!/?\\\"Bar";
    std::string expected = "FOO_-!/?\\\"BAR";
    base::toupper_inplace(str);
    EXPECT_EQ(expected, str);
}

TEST(Strings, ToLowerInPlace_NormalString_ExpectAllLower) {
    std::string str = "FooBar";
    std::string expected = "foobar";
    base::tolower_inplace(str);
    EXPECT_EQ(expected, str);
}

TEST(Strings, ToLowerInPlace_StringWithSpecialChars_ExpectAllLowerAndSpecialCharsUntouched) {
    std::string str = "Foo_-!/?\\\"Bar";
    std::string expected = "foo_-!/?\\\"bar";
    base::tolower_inplace(str);
    EXPECT_EQ(expected, str);
}

TEST(Strings, ReplaceAllInPlace_NormalString_AllCharsReplaced) {
    std::string str = "FoofooBarbar";
    std::string expected = "FeefeeBarbar";
    base::replace_all_inplace(str, 'o', 'e');
    EXPECT_EQ(expected, str);
}

TEST(Strings, ReplaceAllInPlace_NormalStringButSearchCharDoesNotAppear_NoChange) {
    std::string str = "FoofooBarbar";
    std::string expected = str;
    base::replace_all_inplace(str, 'u', 'e');
    EXPECT_EQ(expected, str);
}

TEST(Strings, ConstExpressionStrlen_NormalCString_ProperLength) {
    const char* foobar = "Foobar";
    size_t expected = 6;
    EXPECT_EQ(expected, base::strlen_ce(foobar));
}

TEST(Strings, ConstExpressionStrlen_EmptyCString_ProperLength) {
    const char* foobar = "";
    size_t expected = 0;
    EXPECT_EQ(expected, base::strlen_ce(foobar));
}

TEST(Strings, Split_SimpleStringWithThreeTokensSplitBySlash_ExpectCorrectVector) {
    std::string str = "123/456/789";
    std::vector<std::string> expected = {"123", "456", "789"};

    EXPECT_EQ(expected, base::split(str, '/'));
}

TEST(Strings, Split_SimpleStringWithMultipleSeparatorChars_ExpectCorrectVector) {
    std::string str = "123/456_789-123";
    std::vector<std::string> expected = {"123", "456", "789-123"};

    EXPECT_EQ(expected, base::split(str, {'/', '_'}));
}

TEST(Strings, Split_EmptyStringWithMultipleSeparatorChars_ExpectCorrectVector) {
    std::string str = "";
    std::vector<std::string> expected = {""};

    EXPECT_EQ(expected, base::split(str, {'/', '_'}));
}

TEST(Strings, Split_SeperatorOnlyStringWithMultipleSeparatorChars_ExpectCorrectVector) {
    std::string str = "/";
    std::vector<std::string> expected = {"", ""};

    EXPECT_EQ(expected, base::split(str, {'/', '_'}));
}

TEST(Strings, Split_MultipleSubsequentSeperatorsStringWithMultipleSeparatorChars1_ExpectCorrectVector) {
    std::string str = "Foo//Bar//";
    std::vector<std::string> expected = {"Foo", "Bar", ""};

    EXPECT_EQ(expected, base::split(str, {'/', '_'}));
}

TEST(Strings, Split_MultipleSubsequentSeperatorsStringWithMultipleSeparatorChars2_ExpectCorrectVector) {
    std::string str = "//Foo//Bar";
    std::vector<std::string> expected = {"", "Foo", "Bar"};

    EXPECT_EQ(expected, base::split(str, {'/', '_'}));
}