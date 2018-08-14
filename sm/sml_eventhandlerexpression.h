#pragma once
#include <sm/sml_ids.h>
#include <vector>

namespace sml {
class EventHandlerExpression {
  public:
    EventHandlerExpression();
    EventHandlerExpression(const EventHandlerExpression& orig);
    EventHandlerExpression(const EventHandlerExpression&& orig);
    ~EventHandlerExpression();

    void addObject(Id id);
    bool isValid();

    EventId getEventId();
    StateId getStateId();
    std::vector<GuardId>& getGuards();
    std::vector<ActionId>& getActions();

  private:
    void addState(Id id);
    void addEvent(Id id);
    EventId _triggerEvent;
    std::vector<GuardId> _guards;
    std::vector<ActionId> _actions;
    StateId _destinationState;
};
}

sml::EventHandlerExpression operator>>(sml::EventHandlerExpression&& lhs,
                                       sml::Id& rhs);
sml::EventHandlerExpression operator>>(sml::Id& lhs, sml::Id& rhs);
