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
#include <sm/sml_if_statemachineinstance.h>
#include <sm/sml_simpleaction.h>
#include <sm/sml_simpleguard.h>
#include <sm/sml_state.h>
#include <sm/sml_statemachine.h>

namespace sml
{
State::State() : _name(""), _events(), _entryActions(), _exitActions() {}

State::State(const std::string& name)
    : _name(name), _events(), _entryActions(), _exitActions()
{
}

State::~State() {}

void State::addEventHandler(EventHandlerExpression& expression)
{
    _events[expression.getEventId()].push_back(expression);
}

void State::onEvent(const EventId& eventId, IStateMachineInstance& smi)
{
    if (_events.find(eventId) != _events.end())
    {
        for (auto exp : _events[eventId])
        {
            evaluateEventExpression(exp, smi);
        }
    }
}

void State::evaluateEventExpression(EventHandlerExpression& exp,
                                    IStateMachineInstance& smi)
{
    bool guardState = true;
    for (auto guard : exp.getGuards())
    {
        guardState &= smi.getGuardById(guard)->check(smi.getActionInterface());
        if (!guardState)
        {
            return;
        }
    }

    if (exp.getStateId().getRawId() != NOTDEFINED_BM)
    {
        smi.transitionTo(exp.getStateId(), exp.getActions());
    }
    else
    {
        for (auto action : exp.getActions())
        {
            smi.getActionById(action)->execute(smi.getActionInterface());
        }
    }
}

void State::addEntryHandler(ActionId actionId) { _entryActions.push_back(actionId); }

void State::addExitHandler(ActionId actionId) { _exitActions.push_back(actionId); }

void State::onExit(IStateMachineInstance& smi)
{
    for (auto action : _exitActions)
    {
        smi.getActionById(action)->execute(smi.getActionInterface());
    }
}

void State::onEntry(IStateMachineInstance& smi)
{
    for (auto action : _entryActions)
    {
        smi.getActionById(action)->execute(smi.getActionInterface());
    }
}

std::string State::getName() const { return _name; }
}  // namespace sml
