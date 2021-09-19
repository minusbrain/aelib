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
#include <base/scope_guard.h>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

TEST(ScopeGuard, TestIfCalledIfScopeIsLeft) {
    bool called = false;
    {
        base::scope_guard guard{[&called]() { called = true; }};
        EXPECT_FALSE(called);
    }
    EXPECT_TRUE(called);
}

TEST(ScopeGuard, TestIfCalledIfNestedScopeIsLeft) {
    bool calledInner = false;
    bool calledMid = false;
    bool calledOuter = false;
    {
        base::scope_guard guardOuter{[&calledOuter]() { calledOuter = true; }};
        {
            base::scope_guard guardMid{[&calledMid]() { calledMid = true; }};
            {
                base::scope_guard guardInner{[&calledInner]() { calledInner = true; }};

                EXPECT_FALSE(calledOuter);
                EXPECT_FALSE(calledMid);
                EXPECT_FALSE(calledInner);
            }
            EXPECT_FALSE(calledOuter);
            EXPECT_FALSE(calledMid);
            EXPECT_TRUE(calledInner);
        }
        EXPECT_FALSE(calledOuter);
        EXPECT_TRUE(calledMid);
        EXPECT_TRUE(calledInner);
    }
    EXPECT_TRUE(calledOuter);
    EXPECT_TRUE(calledMid);
    EXPECT_TRUE(calledInner);
}

TEST(ScopeGuard, TestIfCalledIfNestedScopeIsLeftByException) {
    bool calledInner = false;
    bool calledMid = false;
    bool calledOuter = false;
    try {
        base::scope_guard guardOuter{[&calledOuter]() { calledOuter = true; }};
        {
            base::scope_guard guardMid{[&calledMid]() { calledMid = true; }};
            {
                base::scope_guard guardInner{[&calledInner]() { calledInner = true; }};

                EXPECT_FALSE(calledOuter);
                EXPECT_FALSE(calledMid);
                EXPECT_FALSE(calledInner);

                throw 10;
            }
        }
    } catch (int x) {
        ;
    }
    EXPECT_TRUE(calledOuter);
    EXPECT_TRUE(calledMid);
    EXPECT_TRUE(calledInner);
}

TEST(ArmedScopeGuard, TestIfCalledIfScopeIsLeft) {
    bool called = false;
    {
        base::armed_scope_guard guard{[&called]() { called = true; }};
        EXPECT_FALSE(called);
    }
    EXPECT_TRUE(called);
}

TEST(ArmedScopeGuard, TestIfCalledIfNestedScopeIsLeft) {
    bool calledInner = false;
    bool calledMid = false;
    bool calledOuter = false;
    {
        base::armed_scope_guard guardOuter{[&calledOuter]() { calledOuter = true; }};
        {
            base::armed_scope_guard guardMid{[&calledMid]() { calledMid = true; }};
            {
                base::armed_scope_guard guardInner{[&calledInner]() { calledInner = true; }};

                EXPECT_FALSE(calledOuter);
                EXPECT_FALSE(calledMid);
                EXPECT_FALSE(calledInner);
            }
            EXPECT_FALSE(calledOuter);
            EXPECT_FALSE(calledMid);
            EXPECT_TRUE(calledInner);
        }
        EXPECT_FALSE(calledOuter);
        EXPECT_TRUE(calledMid);
        EXPECT_TRUE(calledInner);
    }
    EXPECT_TRUE(calledOuter);
    EXPECT_TRUE(calledMid);
    EXPECT_TRUE(calledInner);
}

TEST(ArmedScopeGuard, TestIfCalledIfNestedScopeIsLeftByException) {
    bool calledInner = false;
    bool calledMid = false;
    bool calledOuter = false;
    try {
        base::armed_scope_guard guardOuter{[&calledOuter]() { calledOuter = true; }};
        {
            base::armed_scope_guard guardMid{[&calledMid]() { calledMid = true; }};
            {
                base::armed_scope_guard guardInner{[&calledInner]() { calledInner = true; }};

                EXPECT_FALSE(calledOuter);
                EXPECT_FALSE(calledMid);
                EXPECT_FALSE(calledInner);

                throw 10;
            }
        }
    } catch (int x) {
        ;
    }
    EXPECT_TRUE(calledOuter);
    EXPECT_TRUE(calledMid);
    EXPECT_TRUE(calledInner);
}

TEST(ArmedScopeGuard, TestIfNotCalledIfScopeIsLeftButDisarmed) {
    bool called = false;
    {
        base::armed_scope_guard guard{[&called]() { called = true; }};
        guard.disarm();
        EXPECT_FALSE(called);
    }
    EXPECT_FALSE(called);
}

TEST(ArmedScopeGuard, TestIfNotCalledIfNestedScopeIsLeftButDisarmed) {
    bool calledInner = false;
    bool calledMid = false;
    bool calledOuter = false;
    {
        base::armed_scope_guard guardOuter{[&calledOuter]() { calledOuter = true; }};
        {
            base::armed_scope_guard guardMid{[&calledMid]() { calledMid = true; }};
            {
                base::armed_scope_guard guardInner{[&calledInner]() { calledInner = true; }};
                guardOuter.disarm();
                guardMid.disarm();
                guardInner.disarm();

                EXPECT_FALSE(calledOuter);
                EXPECT_FALSE(calledMid);
                EXPECT_FALSE(calledInner);
            }
            EXPECT_FALSE(calledOuter);
            EXPECT_FALSE(calledMid);
            EXPECT_FALSE(calledInner);
        }
        EXPECT_FALSE(calledOuter);
        EXPECT_FALSE(calledMid);
        EXPECT_FALSE(calledInner);
    }
    EXPECT_FALSE(calledOuter);
    EXPECT_FALSE(calledMid);
    EXPECT_FALSE(calledInner);
}

TEST(ArmedScopeGuard, TestIfNotCalledIfNestedScopeIsLeftByExceptionButDisarmed) {
    bool calledInner = false;
    bool calledMid = false;
    bool calledOuter = false;
    try {
        base::armed_scope_guard guardOuter{[&calledOuter]() { calledOuter = true; }};
        {
            base::armed_scope_guard guardMid{[&calledMid]() { calledMid = true; }};
            {
                base::armed_scope_guard guardInner{[&calledInner]() { calledInner = true; }};
                guardOuter.disarm();
                guardMid.disarm();
                guardInner.disarm();

                EXPECT_FALSE(calledOuter);
                EXPECT_FALSE(calledMid);
                EXPECT_FALSE(calledInner);

                throw 10;
            }
        }
    } catch (int x) {
        ;
    }
    EXPECT_FALSE(calledOuter);
    EXPECT_FALSE(calledMid);
    EXPECT_FALSE(calledInner);
}