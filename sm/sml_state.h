#pragma once

#include <map>
#include <sm/sml_eventhandlerexpression.h>
#include <string>
#include <vector>

namespace sml {
class IStateMachineInstance;
class State {
  public:
    State();
    State(const std::string&);
    virtual ~State();

    void addEventHandler(EventHandlerExpression& expression);
    void addEntryHandler(ActionId actionId);
    void addExitHandler(ActionId actionId);

    void onEvent(const EventId& eventId, IStateMachineInstance& sm);
    void onExit(IStateMachineInstance& smi);
    void onEntry(IStateMachineInstance& smi);
    std::string getName() const;

  private:
    void evaluateEventExpression(EventHandlerExpression& exp,
                                 IStateMachineInstance& sm);
    std::string _name;
    std::map<EventId, std::vector<EventHandlerExpression>> _events;
    std::vector<ActionId> _entryActions;
    std::vector<ActionId> _exitActions;
};
}
