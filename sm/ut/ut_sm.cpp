#include <iostream>
#include <sm/ut/ut_sm.h>
#include <string>

using ::testing::Sequence;
using ::testing::Return;

UTStatemachine::UTStatemachine()
  : sm(sml::StateMachine::create("StateMachine")), strict_actions(),
    nice_actions() {}
UTStatemachine::~UTStatemachine() {}
void UTStatemachine::SetUp() {}
void UTStatemachine::TearDown() {}

TEST_F(UTStatemachine, InitialState_SetInitialState1_CorrectState) {
    auto SM_STATE_1 = sm.createState("State 1");
    sm.setInitState(SM_STATE_1);

    auto smi = sml::StateMachineInstance<void>::create(sm);
    ASSERT_EQ("State 1", smi.getCurrentStatename());
}

TEST_F(UTStatemachine, InitialState_SetInitialState2_CorrectState) {
    auto SM_STATE_2 = sm.createState("State 2");
    sm.setInitState(SM_STATE_2);

    auto smi = sml::StateMachineInstance<void>::create(sm);
    ASSERT_EQ("State 2", smi.getCurrentStatename());
}

TEST_F(UTStatemachine, InitialState_SendEventForTransition_CorrectNewState) {
    auto SM_STATE_1 = sm.createState("State 1");
    auto SM_STATE_2 = sm.createState("State 2");
    sm.setInitState(SM_STATE_1);
    auto SM_EVENT_1 = sm.createEvent("Event 1");
    sm.assignEvent(SM_STATE_1, SM_EVENT_1 >> SM_STATE_2);

    auto smi = sml::StateMachineInstance<void>::create(sm);
    EXPECT_EQ("State 1", smi.getCurrentStatename());
    smi.onEvent(SM_EVENT_1);
    ASSERT_EQ("State 2", smi.getCurrentStatename());
}

TEST_F(UTStatemachine, InitialState_SendEventForTransition_ExitAction) {
    auto SM_STATE_1 = sm.createState("State 1");
    auto SM_STATE_2 = sm.createState("State 2");
    sm.setInitState(SM_STATE_1);
    auto SM_EVENT_1 = sm.createEvent("Event 1");
    auto SM_ACTION_1 =
      sm.createSimpleAction([&]() { strict_actions.action1(); });
    auto SM_ACTION_2 =
      sm.createSimpleAction([&]() { strict_actions.action2(); });
    sm.onEntry(SM_STATE_1, SM_ACTION_2);
    sm.onExit(SM_STATE_1, SM_ACTION_1);
    sm.assignEvent(SM_STATE_1, SM_EVENT_1 >> SM_STATE_2);

    auto smi = sml::StateMachineInstance<void>::create(sm);
    EXPECT_CALL(strict_actions, action1()).Times(1);
    smi.onEvent(SM_EVENT_1);
}

TEST_F(UTStatemachine, InitialState_SendEventForTransition_EntryAction) {
    auto SM_STATE_1 = sm.createState("State 1");
    auto SM_STATE_2 = sm.createState("State 2");
    sm.setInitState(SM_STATE_1);
    auto SM_EVENT_1 = sm.createEvent("Event 1");
    auto SM_ACTION_1 =
      sm.createSimpleAction([&]() { strict_actions.action1(); });
    auto SM_ACTION_2 =
      sm.createSimpleAction([&]() { strict_actions.action2(); });
    sm.onEntry(SM_STATE_2, SM_ACTION_2);
    sm.onExit(SM_STATE_2, SM_ACTION_1);
    sm.assignEvent(SM_STATE_1, SM_EVENT_1 >> SM_STATE_2);

    auto smi = sml::StateMachineInstance<void>::create(sm);
    EXPECT_CALL(strict_actions, action2()).Times(1);
    smi.onEvent(SM_EVENT_1);
}

TEST_F(
  UTStatemachine,
  InitialState_SendEventForTransition_CorrectSequenceOfExitAndEntryActions) {
    Sequence s1;
    auto SM_STATE_1 = sm.createState("State 1");
    auto SM_STATE_2 = sm.createState("State 2");
    sm.setInitState(SM_STATE_1);
    auto SM_EVENT_1 = sm.createEvent("Event 1");
    auto SM_ACTION_1 =
      sm.createSimpleAction([&]() { strict_actions.action1(); });
    auto SM_ACTION_2 =
      sm.createSimpleAction([&]() { strict_actions.action2(); });
    auto SM_ACTION_3 =
      sm.createSimpleAction([&]() { strict_actions.action3(); });
    auto SM_ACTION_4 =
      sm.createSimpleAction([&]() { strict_actions.action4(); });
    sm.onEntry(SM_STATE_2, SM_ACTION_3);
    sm.onEntry(SM_STATE_2, SM_ACTION_4);
    sm.onExit(SM_STATE_1, SM_ACTION_1);
    sm.onExit(SM_STATE_1, SM_ACTION_2);
    sm.assignEvent(SM_STATE_1, SM_EVENT_1 >> SM_STATE_2);

    auto smi = sml::StateMachineInstance<void>::create(sm);
    EXPECT_CALL(strict_actions, action1()).Times(1).InSequence(s1);
    EXPECT_CALL(strict_actions, action2()).Times(1).InSequence(s1);
    EXPECT_CALL(strict_actions, action3()).Times(1).InSequence(s1);
    EXPECT_CALL(strict_actions, action4()).Times(1).InSequence(s1);
    smi.onEvent(SM_EVENT_1);
}

TEST_F(UTStatemachine,
       InitialState_SendEventForTransitionAndAction_CorrectNewStateAndAction) {
    auto SM_STATE_1 = sm.createState("State 1");
    auto SM_STATE_2 = sm.createState("State 2");
    sm.setInitState(SM_STATE_1);
    auto SM_EVENT_1 = sm.createEvent("Event 1");
    auto SM_ACTION_1 =
      sm.createSimpleAction([&]() { strict_actions.action1(); });
    sm.assignEvent(SM_STATE_1, SM_EVENT_1 >> SM_ACTION_1 >> SM_STATE_2);

    auto smi = sml::StateMachineInstance<void>::create(sm);
    EXPECT_CALL(strict_actions, action1()).Times(1);
    smi.onEvent(SM_EVENT_1);
    ASSERT_EQ("State 2", smi.getCurrentStatename());
}

TEST_F(UTStatemachine,
       InitialState_SendEventForTransitionAndAction_CorrectSequenceOfActions) {
    Sequence s1;
    auto SM_STATE_1 = sm.createState("State 1");
    auto SM_STATE_2 = sm.createState("State 2");
    sm.setInitState(SM_STATE_1);
    auto SM_EVENT_1 = sm.createEvent("Event 1");
    auto SM_ACTION_1 =
      sm.createSimpleAction([&]() { strict_actions.action1(); });
    auto SM_ACTION_2 =
      sm.createSimpleAction([&]() { strict_actions.action2(); });
    auto SM_ACTION_3 =
      sm.createSimpleAction([&]() { strict_actions.action3(); });
    sm.onEntry(SM_STATE_2, SM_ACTION_3);
    sm.onExit(SM_STATE_1, SM_ACTION_1);
    sm.assignEvent(SM_STATE_1, SM_EVENT_1 >> SM_ACTION_2 >> SM_STATE_2);

    auto smi = sml::StateMachineInstance<void>::create(sm);
    EXPECT_CALL(strict_actions, action1()).Times(1).InSequence(s1);
    EXPECT_CALL(strict_actions, action2()).Times(1).InSequence(s1);
    EXPECT_CALL(strict_actions, action3()).Times(1).InSequence(s1);
    smi.onEvent(SM_EVENT_1);
}

TEST_F(
  UTStatemachine,
  InterfaceActionCall_SendEventForTransitionAndAction_OnlyCorrectActionAtCorrectInterface) {
    auto SM_STATE_1 = sm.createState("State 1");
    auto SM_STATE_2 = sm.createState("State 2");
    sm.setInitState(SM_STATE_1);

    auto SM_EVENT_1 = sm.createEvent("Event 1");

    auto SM_ACTION_1 =
      sm.createInterfaceAction<ActionMock>(std::mem_fn(&ActionMock::action1));

    sm.assignEvent(SM_STATE_1, SM_EVENT_1 >> SM_STATE_2 >> SM_ACTION_1);

    auto smi1 =
      sml::StateMachineInstance<ActionMock>::create(sm, &nice_actions);
    auto smi2 =
      sml::StateMachineInstance<ActionMock>::create(sm, &strict_actions);

    EXPECT_CALL(nice_actions, action2()).Times(0);
    EXPECT_CALL(nice_actions, action1()).Times(1);
    smi1.onEvent(SM_EVENT_1);
}

TEST_F(
  UTStatemachine,
  InterfaceGuardCall_SendEventForGuardProtectedTransition_GuardCallAndCorrectPostState) {
    auto SM_STATE_1 = sm.createState("State 1");
    auto SM_STATE_2 = sm.createState("State 2");
    sm.setInitState(SM_STATE_1);
    auto SM_EVENT_1 = sm.createEvent("Event 1");
    auto SM_GUARD_1 = sm.createInterfaceGuard<ActionMock>(
      std::mem_fn(&ActionMock::guard1), true);
    sm.assignEvent(SM_STATE_1, SM_EVENT_1 >> SM_GUARD_1 >> SM_STATE_2);

    auto smi1 =
      sml::StateMachineInstance<ActionMock>::create(sm, &nice_actions);
    auto smi2 =
      sml::StateMachineInstance<ActionMock>::create(sm, &strict_actions);

    EXPECT_CALL(nice_actions, guard1()).Times(1).WillOnce(Return(true));
    smi1.onEvent("Event 1");
    EXPECT_EQ(std::string("State 2"), smi1.getCurrentStatename());
}

TEST_F(
  UTStatemachine,
  InterfaceGuardCall_SendEventForFailingGuardProtectedTransition_GuardCallAndNoStateChange) {
    auto SM_STATE_1 = sm.createState("State 1");
    auto SM_STATE_2 = sm.createState("State 2");
    sm.setInitState(SM_STATE_1);
    auto SM_EVENT_1 = sm.createEvent("Event 1");
    auto SM_GUARD_1 = sm.createInterfaceGuard<ActionMock>(
      std::mem_fn(&ActionMock::guard1), true);
    sm.assignEvent(SM_STATE_1, SM_EVENT_1 >> SM_GUARD_1 >> SM_STATE_2);

    auto smi1 =
      sml::StateMachineInstance<ActionMock>::create(sm, &nice_actions);
    auto smi2 =
      sml::StateMachineInstance<ActionMock>::create(sm, &strict_actions);

    EXPECT_CALL(nice_actions, guard1()).Times(1).WillOnce(Return(false));
    smi1.onEvent("Event 1");
    EXPECT_EQ(std::string("State 1"), smi1.getCurrentStatename());
}
