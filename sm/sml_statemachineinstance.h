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
#pragma once

#include <memory>
#include <string>
#include <vector>

#include "sml_ids.h"
#include "sml_if_action.h"
#include "sml_if_guard.h"
#include "sml_if_statemachineinstance.h"
#include "sml_state.h"
#include "sml_statemachine.h"

namespace sml {
class StateMachine;
class IAction;
class IGuard;

template <class T_If>
class StateMachineInstance : public IStateMachineInstance {
   public:
    static StateMachineInstance create(StateMachine& sm, T_If* actionIf = nullptr);
    static StateMachineInstance* createOnHeap(StateMachine& sm, T_If* actionIf = nullptr);
    virtual ~StateMachineInstance();

    virtual std::string getCurrentStatename() const;
    virtual void onEvent(const std::string& eventName);
    virtual void onEvent(const EventId& eventId);

    virtual void transitionTo(StateId stateId, const std::vector<ActionId>& actions);
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
StateMachineInstance<T_If> StateMachineInstance<T_If>::create(StateMachine& sm, T_If* actionIf) {
    return StateMachineInstance<T_If>(sm, actionIf);
}

template <class T_If>
StateMachineInstance<T_If>* StateMachineInstance<T_If>::createOnHeap(StateMachine& sm, T_If* actionIf) {
    return new StateMachineInstance<T_If>(sm, actionIf);
}

template <class T_If>
StateMachineInstance<T_If>::StateMachineInstance(StateMachine& sm, T_If* actionIf)
    : _sm(sm), _currentState(sm.getInitState()), _if(actionIf) {}

template <class T_If>
StateMachineInstance<T_If>::~StateMachineInstance() {}

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
void StateMachineInstance<T_If>::transitionTo(StateId stateId, const std::vector<ActionId>& actions) {
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
}  // namespace sml
