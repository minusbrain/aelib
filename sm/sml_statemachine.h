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

#include <sm/sml_event.h>
#include <sm/sml_ids.h>
#include <sm/sml_interfaceaction.h>
#include <sm/sml_interfaceguard.h>

#include <functional>
#include <map>
#include <memory>
#include <string>

namespace sml
{
static const unsigned int STATE_BM = 0x01000000;
static const unsigned int ACTION_BM = 0x02000000;
static const unsigned int EVENT_BM = 0x04000000;
static const unsigned int GUARD_BM = 0x08000000;
static const unsigned int NOTDEFINED_BM = 0xFF000000;
static const unsigned int COUNTER_MAX = 0x00FFFFFF;

class EventHandlerExpression;
class State;
class IAction;
class IGuard;

class StateMachine
{
   public:
    virtual ~StateMachine();

    static StateMachine create(const std::string& name);

    StateId createState(const std::string& name);
    EventId createEvent(const std::string& name);
    GuardId createSimpleGuard(std::function<bool(void)>, bool);
    ActionId createSimpleAction(std::function<void(void)>);
    template <class T_If>
    ActionId createInterfaceAction(std::function<void(T_If&)>);
    template <class T_If>
    GuardId createInterfaceGuard(std::function<bool(T_If&)>, bool);

    void onEntry(StateId stateId, ActionId actionId);
    void onExit(StateId stateId, ActionId actionId);
    void assignEvent(StateId, EventHandlerExpression);
    void setInitState(StateId state);

    StateId getInitState();
    EventId getEventIdByName(const std::string& eventName);
    State* getStateById(StateId);
    IAction* getActionById(ActionId);
    IGuard* getGuardById(GuardId);

   private:
    std::string _name;

    std::map<StateId, State> _stateMap;
    std::map<EventId, Event> _eventMap;
    std::map<ActionId, IAction*> _actionMap;
    std::map<GuardId, IGuard*> _guardMap;

    unsigned int _stateCounter;
    unsigned int _eventCounter;
    unsigned int _actionCounter;
    unsigned int _guardCounter;
    StateId _initState;

    StateMachine(const std::string& name);
    ActionId createInterfaceActionHelper(IAction* ptr);
    GuardId createInterfaceGuardHelper(IGuard* ptr);
};

template <class T_If>
ActionId StateMachine::createInterfaceAction(std::function<void(T_If&)> fctToCall)
{
    return createInterfaceActionHelper(new InterfaceAction<T_If>(fctToCall));
}

template <class T_If>
GuardId StateMachine::createInterfaceGuard(std::function<bool(T_If&)> fctToCall,
                                           bool expectedResult)
{
    return createInterfaceGuardHelper(
        new InterfaceGuard<T_If>(fctToCall, expectedResult));
}
}  // namespace sml
