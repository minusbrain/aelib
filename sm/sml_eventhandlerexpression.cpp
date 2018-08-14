#include <aelib/sm/sml.h>

namespace sml {

	EventHandlerExpression::EventHandlerExpression(const EventHandlerExpression&& orig) :
		_triggerEvent(orig._triggerEvent),
		_guards(orig._guards),
		_actions(orig._actions),
		_destinationState(orig._destinationState)
	{
	}

	EventHandlerExpression::EventHandlerExpression(const EventHandlerExpression& orig) :
		_triggerEvent(orig._triggerEvent),
		_guards(orig._guards),
		_actions(orig._actions),
		_destinationState(orig._destinationState)
	{
	}

	EventHandlerExpression::EventHandlerExpression() :
		_triggerEvent(NOTDEFINED_BM),
		_guards(),
		_actions(),
		_destinationState(NOTDEFINED_BM)
	{
	}


	EventHandlerExpression::~EventHandlerExpression()
	{
	}

	void EventHandlerExpression::addObject(Id idObj) {
		unsigned int id = idObj.getRawId();

		if ((id & STATE_BM) == STATE_BM) {
			addState(idObj);
		} 
		else if ((id & EVENT_BM) == EVENT_BM) {
			addEvent(idObj);
		}
		else if ((id & GUARD_BM) == GUARD_BM) {
			_guards.push_back(idObj);
		}
		else if ((id & ACTION_BM) == ACTION_BM) {
			_actions.push_back(idObj);
		}
	}

	void EventHandlerExpression::addState(Id id)
	{
		if (_destinationState.getRawId() != NOTDEFINED_BM) {
			// TODO Errorhandling
		}

		_destinationState = id;
	}

	void EventHandlerExpression::addEvent(Id id)
	{
		if (_triggerEvent.getRawId() != NOTDEFINED_BM) {
			// TODO Errorhandling
		}

		_triggerEvent = id;
	}

	sml::EventId EventHandlerExpression::getEventId()
	{
		return _triggerEvent;
	}

	sml::StateId EventHandlerExpression::getStateId()
	{
		return _destinationState;
	}

	bool EventHandlerExpression::isValid()
	{
		if (_triggerEvent.getRawId() == NOTDEFINED_BM)
			return false;

		if (_destinationState.getRawId() == NOTDEFINED_BM && _actions.empty())
			return false;

		return true;
	}

	std::vector<GuardId>& EventHandlerExpression::getGuards()
	{
		return _guards;
	}

	std::vector<ActionId>& EventHandlerExpression::getActions()
	{
		return _actions;
	}
}

sml::EventHandlerExpression operator>> (sml::EventHandlerExpression&& lhs, sml::Id& rhs) {
	sml::EventHandlerExpression retVal(std::move(lhs));
	retVal.addObject(rhs);
	return retVal;
}

sml::EventHandlerExpression operator>> (sml::Id& lhs, sml::Id& rhs) {
	sml::EventHandlerExpression retVal;
	retVal.addObject(lhs);
	retVal.addObject(rhs);
	return retVal;
}
