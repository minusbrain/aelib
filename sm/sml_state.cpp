#include <sm/sml_if_statemachineinstance.h>
#include <sm/sml_simpleaction.h>
#include <sm/sml_simpleguard.h>
#include <sm/sml_state.h>
#include <sm/sml_statemachine.h>

namespace sml {
State::State() : _name(""), _events(), _entryActions(), _exitActions() {}

State::State(const std::string& name)
  : _name(name), _events(), _entryActions(), _exitActions() {}

State::~State() {}

void State::addEventHandler(EventHandlerExpression& expression) {
    _events[expression.getEventId()].push_back(expression);
}

void State::onEvent(const EventId& eventId, IStateMachineInstance& smi) {
    if (_events.find(eventId) != _events.end()) {
        for (auto exp : _events[eventId]) {
            evaluateEventExpression(exp, smi);
        }
    }
}

void State::evaluateEventExpression(EventHandlerExpression& exp,
                                    IStateMachineInstance& smi) {
    bool guardState = true;
    for (auto guard : exp.getGuards()) {
        guardState &= smi.getGuardById(guard)->check(smi.getActionInterface());
        if (!guardState) {
            return;
        }
    }

    if (exp.getStateId().getRawId() != NOTDEFINED_BM) {
        smi.transitionTo(exp.getStateId(), exp.getActions());
    }
    else {
        for (auto action : exp.getActions()) {
            smi.getActionById(action)->execute(smi.getActionInterface());
        }
    }
}

void State::addEntryHandler(ActionId actionId) {
    _entryActions.push_back(actionId);
}

void State::addExitHandler(ActionId actionId) {
    _exitActions.push_back(actionId);
}

void State::onExit(IStateMachineInstance& smi) {
    for (auto action : _exitActions) {
        smi.getActionById(action)->execute(smi.getActionInterface());
    }
}

void State::onEntry(IStateMachineInstance& smi) {
    for (auto action : _entryActions) {
        smi.getActionById(action)->execute(smi.getActionInterface());
    }
}

std::string State::getName() const { return _name; }
}
