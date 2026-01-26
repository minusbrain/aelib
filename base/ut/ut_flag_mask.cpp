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
#include <base/flag_mask.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

enum class Simple : uint32_t { a = 0x01, b = 0x02, c = 0x80000000 };

enum class SimpleChar : char { a = 0x01, b = 0x02, c = 0x40 };

TEST(flag_mask, ReadMeExample) {
    enum class MyFlags : unsigned char { FLAG_A = 0x01, FLAG_B = 0x02, FLAG_C = 0x40 };

    base::flag_mask<MyFlags> flags{MyFlags::FLAG_A, MyFlags::FLAG_C};
    std::cout << flags << "\n";  // Prints 01000001
    flags += MyFlags::FLAG_B;
    std::cout << flags << "\n";  // Prints 01000011
}

TEST(flag_mask, CreateSimpleFM_UseIndexOperatorToSetAndCheckState) {
    base::flag_mask<Simple> mask;
    mask[Simple::c] = true;
    mask[Simple::a] = false;
    EXPECT_TRUE(mask[Simple::c]);
    EXPECT_FALSE(mask[Simple::a]);
}

TEST(flag_mask, CreateSimpleFM_CheckAllAreUnset_ExpectUnset) {
    base::flag_mask<Simple> mask;
    EXPECT_FALSE(mask.check(Simple::a));
    EXPECT_FALSE(mask.check(Simple::b));
    EXPECT_FALSE(mask.check(Simple::c));
}

TEST(flag_mask, CreatePreinitSimpleFM_CheckSetStatus_ExpectOnlyCorrectFlagsSet) {
    base::flag_mask<Simple> mask(0x80000001);
    EXPECT_TRUE(mask.check(Simple::a));
    EXPECT_FALSE(mask.check(Simple::b));
    EXPECT_TRUE(mask.check(Simple::c));
}

TEST(flag_mask, AddFlagToFM_CheckSetStatus_ExpectOnlyCorrectFlagSet) {
    base::flag_mask<Simple> mask;
    mask.set(Simple::b);
    EXPECT_FALSE(mask.check(Simple::a));
    EXPECT_TRUE(mask.check(Simple::b));
    EXPECT_FALSE(mask.check(Simple::c));
}

TEST(flag_mask, CreatePreinitSimpleFM_UnsetFlagAndCheckSetStatus_ExpectOnlyCorrectFlagSet) {
    base::flag_mask<Simple> mask(0x80000001);
    mask.unset(Simple::a);
    EXPECT_FALSE(mask.check(Simple::a));
    EXPECT_FALSE(mask.check(Simple::b));
    EXPECT_TRUE(mask.check(Simple::c));
}

TEST(flag_mask, CreatePreinitSimpleFM_ClearAndCheck_ExpectUnset) {
    base::flag_mask<Simple> mask(0x80000001);
    mask.clear();
    EXPECT_FALSE(mask.check(Simple::a));
    EXPECT_FALSE(mask.check(Simple::b));
    EXPECT_FALSE(mask.check(Simple::c));
}

TEST(flag_mask, CreatePreinitSimpleFM_ClearSetSetUnsetAndCheck_ExpectOnlyCorrectFlagSet) {
    base::flag_mask<Simple> mask(0x80000001);
    mask.clear().set(Simple::b).set(Simple::a).unset(Simple::b);
    EXPECT_TRUE(mask.check(Simple::a));
    EXPECT_FALSE(mask.check(Simple::b));
    EXPECT_FALSE(mask.check(Simple::c));
}

TEST(flag_mask, CreateSimpleFM_SetAllUnsetOne_ExpectOnlyCorrectFlagSet) {
    base::flag_mask<Simple> mask;
    mask.set_all().unset(Simple::b);
    EXPECT_TRUE(mask.check(Simple::a));
    EXPECT_FALSE(mask.check(Simple::b));
    EXPECT_TRUE(mask.check(Simple::c));
}

TEST(flag_mask, CreateSimpleFM_AddTwoFlagsCheckAllSetFlags_ExpectAllFlagsSet) {
    base::flag_mask<Simple> mask;
    mask.set(Simple::c).set(Simple::a);
    EXPECT_TRUE(mask.check_all({Simple::a, Simple::c}));
    EXPECT_FALSE(mask.check_all({Simple::a, Simple::b}));
}

TEST(flag_mask, CreatePreinitSimpleCharFM_TestAllFunctions_ExpectOnlyCorrectFlagSet) {
    base::flag_mask<SimpleChar> mask(0x41);
    mask.clear().set(SimpleChar::b).set(SimpleChar::a).unset(SimpleChar::b);
    EXPECT_TRUE(mask.check(SimpleChar::a));
    EXPECT_FALSE(mask.check(SimpleChar::b));
    EXPECT_FALSE(mask.check(SimpleChar::c));
}

TEST(flag_mask, CreatePreinitSimpleCharFM_Check_ExpectOnlyCorrectFlagSet) {
    base::flag_mask<SimpleChar> mask(0x41);
    EXPECT_TRUE(mask.check(SimpleChar::a));
    EXPECT_FALSE(mask.check(SimpleChar::b));
    EXPECT_TRUE(mask.check(SimpleChar::c));
}

TEST(flag_mask, CreateSimpleFM_AddOneFlagSyntacticSugarCheckAllSetFlags_ExpectAllFlagsSet) {
    base::flag_mask<Simple> mask;
    mask += Simple::a;
    EXPECT_TRUE(mask.check(Simple::a));
}

TEST(flag_mask, CreateSimpleFM_RemoveOneFlagSyntacticSugarCheckAllSetFlags_ExpectAllFlagsSet) {
    base::flag_mask<Simple> mask;
    mask += Simple::a;
    mask -= Simple::a;
    EXPECT_FALSE(mask.check(Simple::a));
}

TEST(flag_mask, CreateSimpleFM_AddMultiple_ExpectAllFlagsSet) {
    base::flag_mask<Simple> mask;
    mask += {Simple::a, Simple::b};
    EXPECT_TRUE(mask.check_all({Simple::a, Simple::b}));
}

TEST(flag_mask, CreateSimpleFM_RemoveMultiple_ExpectAllFlagsSet) {
    base::flag_mask<Simple> mask;
    mask += {Simple::a, Simple::b};
    mask -= {Simple::a, Simple::c};
    EXPECT_TRUE(mask.check_none({Simple::a, Simple::c}));
    EXPECT_TRUE(mask.check(Simple::b));
}

TEST(flag_mask, StreamOut_7Bit_Bitmask) {
    enum class MyFlags : char { FLAG_A = 0x01, FLAG_B = 0x02, FLAG_C = 0x40 };

    base::flag_mask<MyFlags> flags{MyFlags::FLAG_A, MyFlags::FLAG_C};
    std::stringstream ss;
    ss << flags;
    EXPECT_EQ("1000001", ss.str());
}

TEST(flag_mask, StreamOut_8Bit_Bitmask) {
    enum class MyFlags : unsigned char { FLAG_A = 0x01, FLAG_B = 0x02, FLAG_C = 0x40 };

    base::flag_mask<MyFlags> flags{MyFlags::FLAG_A, MyFlags::FLAG_C};
    std::stringstream ss;
    ss << flags;
    EXPECT_EQ("01000001", ss.str());
}

TEST(flag_mask, StreamOut_32Bit_Bitmask) {
    enum class MyFlags : unsigned int { FLAG_A = 0x01, FLAG_B = 0x02, FLAG_C = 0x80000000 };

    base::flag_mask<MyFlags> flags{MyFlags::FLAG_A, MyFlags::FLAG_C};
    std::stringstream ss;
    ss << flags;
    EXPECT_EQ("10000000000000000000000000000001", ss.str());
}

TEST(flag_mask, ImplicitFromInteger) {
    enum class MyFlags : unsigned int { FLAG_A = 0x01, FLAG_B = 0x02, FLAG_C = 0x80000000 };

    auto my_function = [](base::flag_mask<MyFlags> flags) {
        base::flag_mask<MyFlags> expected{MyFlags::FLAG_A, MyFlags::FLAG_C};
        EXPECT_EQ(expected, flags);
    };

    my_function(0x80000001);
}
