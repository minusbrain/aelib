#pragma once
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sm/sml.h>
#include <sm/ut/actionmock.h>

using testing::StrictMock;
using testing::NiceMock;

class UTStatemachine : public ::testing::Test {
  public:
    UTStatemachine();
    ~UTStatemachine();

    void SetUp();
    void TearDown();

  protected:
    sml::StateMachine sm;
    StrictMock<ActionMock> strict_actions;
    NiceMock<ActionMock> nice_actions;
};
