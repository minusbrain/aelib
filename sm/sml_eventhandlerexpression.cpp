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
#include <sm/sml.h>

namespace sml
{
EventHandlerExpression::EventHandlerExpression(const EventHandlerExpression&& orig)
    : _triggerEvent(orig._triggerEvent),
      _guards(orig._guards),
      _actions(orig._actions),
      _destinationState(orig._destinationState)
{
}

EventHandlerExpression::EventHandlerExpression(const EventHandlerExpression& orig)
    : _triggerEvent(orig._triggerEvent),
      _guards(orig._guards),
      _actions(orig._actions),
      _destinationState(orig._destinationState)
{
}

EventHandlerExpression::EventHandlerExpression()
    : _triggerEvent(NOTDEFINED_BM),
      _guards(),
      _actions(),
      _destinationState(NOTDEFINED_BM)
{
}

EventHandlerExpression::~EventHandlerExpression() {}

void EventHandlerExpression::addObject(Id idObj)
{
    unsigned int id = idObj.getRawId();

    if ((id & STATE_BM) == STATE_BM)
    {
        addState(idObj);
    }
    else if ((id & EVENT_BM) == EVENT_BM)
    {
        addEvent(idObj);
    }
    else if ((id & GUARD_BM) == GUARD_BM)
    {
        _guards.push_back(idObj);
    }
    else if ((id & ACTION_BM) == ACTION_BM)
    {
        _actions.push_back(idObj);
    }
}

void EventHandlerExpression::addState(Id id)
{
    if (_destinationState.getRawId() != NOTDEFINED_BM)
    {
        // TODO Errorhandling
    }

    _destinationState = id;
}

void EventHandlerExpression::addEvent(Id id)
{
    if (_triggerEvent.getRawId() != NOTDEFINED_BM)
    {
        // TODO Errorhandling
    }

    _triggerEvent = id;
}

sml::EventId EventHandlerExpression::getEventId() { return _triggerEvent; }

sml::StateId EventHandlerExpression::getStateId() { return _destinationState; }

bool EventHandlerExpression::isValid()
{
    if (_triggerEvent.getRawId() == NOTDEFINED_BM) return false;

    if (_destinationState.getRawId() == NOTDEFINED_BM && _actions.empty()) return false;

    return true;
}

std::vector<GuardId>& EventHandlerExpression::getGuards() { return _guards; }

std::vector<ActionId>& EventHandlerExpression::getActions() { return _actions; }
}  // namespace sml

sml::EventHandlerExpression operator>>(sml::EventHandlerExpression&& lhs, sml::Id& rhs)
{
    sml::EventHandlerExpression retVal(std::move(lhs));
    retVal.addObject(rhs);
    return retVal;
}

sml::EventHandlerExpression operator>>(sml::Id& lhs, sml::Id& rhs)
{
    sml::EventHandlerExpression retVal;
    retVal.addObject(lhs);
    retVal.addObject(rhs);
    return retVal;
}
