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
