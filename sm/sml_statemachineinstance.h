#pragma once

#include <memory>
#include <sm/sml_ids.h>
#include <sm/sml_if_action.h>
#include <sm/sml_if_guard.h>
#include <sm/sml_if_statemachineinstance.h>
#include <sm/sml_state.h>
#include <sm/sml_statemachine.h>
#include <string>
#include <vector>

namespace sml {
class StateMachine;
class IAction;
class IGuard;

template <class T_If>
class StateMachineInstance : public IStateMachineInstance {
  public:
    static StateMachineInstance create(StateMachine& sm,
                                       T_If* actionIf = nullptr);
    static StateMachineInstance* createOnHeap(StateMachine& sm,
                                              T_If* actionIf = nullptr);
    virtual ~StateMachineInstance();

    virtual std::string getCurrentStatename() const;
    virtual void onEvent(const std::string& eventName);
    virtual void onEvent(const EventId& eventId);

    virtual void transitionTo(StateId stateId,
                              const std::vector<ActionId>& actions);
    virtual IAction* getActionById(ActionId) const;
    virtual IGuard* getGuardById(GuardId) const;
    virtual void* getActionInterface() const;

  private:
    StateMachineInstance(StateMachine& sm, T_If* actionIf);
    StateMachineInstance& operator=(const StateMachineInstance& rhs);

    StateMachine& _sm;
    StateId _currentState;
    T_If* _if;
};

template <class T_If>
StateMachineInstance<T_If> StateMachineInstance<T_If>::create(StateMachine& sm,
                                                              T_If* actionIf) {
    return StateMachineInstance<T_If>(sm, actionIf);
}

template <class T_If>
StateMachineInstance<T_If>*
StateMachineInstance<T_If>::createOnHeap(StateMachine& sm, T_If* actionIf) {
    return new StateMachineInstance<T_If>(sm, actionIf);
}

template <class T_If>
StateMachineInstance<T_If>::StateMachineInstance(StateMachine& sm,
                                                 T_If* actionIf)
  : _sm(sm), _currentState(sm.getInitState()), _if(actionIf) {}

template <class T_If> StateMachineInstance<T_If>::~StateMachineInstance() {}

template <class T_If>
void StateMachineInstance<T_If>::onEvent(const std::string& eventName) {
    EventId eventId = _sm.getEventIdByName(eventName);
    if (eventId.getRawId() == NOTDEFINED_BM) {
        // TODO: Errorhandling
        return;
    }
    onEvent(eventId);
}

template <class T_If>
void StateMachineInstance<T_If>::onEvent(const EventId& eventId) {
    State* state = _sm.getStateById(_currentState);
    state->onEvent(eventId, *this);
}

template <class T_If>
IAction* StateMachineInstance<T_If>::getActionById(ActionId id) const {
    return _sm.getActionById(id);
}

template <class T_If>
IGuard* StateMachineInstance<T_If>::getGuardById(GuardId id) const {
    return _sm.getGuardById(id);
}

template <class T_If>
void StateMachineInstance<T_If>::transitionTo(
  StateId stateId, const std::vector<ActionId>& actions) {
    _sm.getStateById(_currentState)->onExit(*this);
    for (auto action : actions) {
        getActionById(action)->execute((void*)_if);
    }
    _currentState = stateId;
    _sm.getStateById(_currentState)->onEntry(*this);
}

template <class T_If>
std::string StateMachineInstance<T_If>::getCurrentStatename() const {
    return _sm.getStateById(_currentState)->getName();
}

template <class T_If>
void* StateMachineInstance<T_If>::getActionInterface() const {
    return (void*)_if;
}
}
