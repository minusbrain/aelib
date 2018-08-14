#include <sm/sml_statemachine.h>

#include <algorithm>
#include <map>

#include <sm/sml_event.h>
#include <sm/sml_simpleaction.h>
#include <sm/sml_simpleguard.h>
#include <sm/sml_state.h>

namespace sml {
StateMachine::StateMachine(const std::string& name)
  : _name(name), _stateMap(), _eventMap(), _actionMap(), _guardMap(),
    _stateCounter(0), _eventCounter(0), _actionCounter(0), _guardCounter(0),
    _initState(NOTDEFINED_BM) {}

StateMachine::~StateMachine() {
    for (auto x : _actionMap) {
        delete x.second;
    }

    for (auto x : _guardMap) {
        delete x.second;
    }
}

StateMachine StateMachine::create(const std::string& name) {
    return StateMachine(name);
}

StateId StateMachine::createState(const std::string& name) {
    StateId newId(STATE_BM | ++_stateCounter);
    _stateMap[newId] = State(name);
    if (_initState.getRawId() == NOTDEFINED_BM) {
        _initState = newId;
    }
    return newId;
}

EventId StateMachine::createEvent(const std::string& name) {
    EventId newId(EVENT_BM | ++_eventCounter);
    _eventMap[newId] = Event(name);
    return newId;
}

GuardId StateMachine::createSimpleGuard(std::function<bool(void)> fctToCall,
                                        bool expectedResult) {
    GuardId newId(GUARD_BM | ++_guardCounter);
    _guardMap[newId] = new SimpleGuard(fctToCall, expectedResult);
    return newId;
}

ActionId StateMachine::createSimpleAction(std::function<void(void)> fctToCall) {
    ActionId newId(ACTION_BM | ++_actionCounter);
    _actionMap[newId] = new SimpleAction(fctToCall);
    return newId;
}

void StateMachine::assignEvent(StateId stateId,
                               EventHandlerExpression expression) {
    if (_stateMap.find(stateId) == _stateMap.end()) {
        // TODO: Errohandling
    }
    _stateMap[stateId].addEventHandler(expression);
}

void StateMachine::setInitState(StateId state) {
    if (_stateMap.find(state) == _stateMap.end()) {
        // TODO: Errohandling
    }
    _initState = state;
}

StateId StateMachine::getInitState() { return _initState; }

EventId StateMachine::getEventIdByName(const std::string& eventName) {
    auto it =
      std::find_if(_eventMap.begin(), _eventMap.end(),
                   [eventName](const std::pair<EventId, Event>& pair) -> bool {
                       return pair.second.getName() == eventName;
                   });

    if (it != _eventMap.end()) {
        return it->first;
    }
    else {
        return EventId(NOTDEFINED_BM);
    }
}

State* StateMachine::getStateById(StateId id) { return &_stateMap[id]; }

IAction* StateMachine::getActionById(ActionId id) { return _actionMap[id]; }

IGuard* StateMachine::getGuardById(GuardId id) { return _guardMap[id]; }

void StateMachine::onEntry(StateId stateId, ActionId actionId) {
    if (_stateMap.find(stateId) == _stateMap.end()) {
        // TODO: Errohandling
    }
    _stateMap[stateId].addEntryHandler(actionId);
}

void StateMachine::onExit(StateId stateId, ActionId actionId) {
    if (_stateMap.find(stateId) == _stateMap.end()) {
        // TODO: Errohandling
    }
    _stateMap[stateId].addExitHandler(actionId);
}

ActionId StateMachine::createInterfaceActionHelper(IAction* ptr) {
    ActionId newId(ACTION_BM | ++_actionCounter);
    _actionMap[newId] = ptr;
    return newId;
}

GuardId StateMachine::createInterfaceGuardHelper(IGuard* ptr) {
    GuardId newId(GUARD_BM | ++_guardCounter);
    _guardMap[newId] = ptr;
    return newId;
}
}
