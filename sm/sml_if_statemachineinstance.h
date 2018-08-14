#pragma once

#include <string>
#include <vector>

#include <sm/sml_ids.h>

namespace sml {
class IAction;
class IGuard;

class IStateMachineInstance {
  public:
    virtual ~IStateMachineInstance(){};

    virtual std::string getCurrentStatename() const = 0;
    virtual void onEvent(const std::string& eventName) = 0;
    virtual void onEvent(const EventId& eventId) = 0;

    virtual void transitionTo(StateId stateId,
                              const std::vector<ActionId>& actions) = 0;

    virtual IAction* getActionById(ActionId) const = 0;
    virtual IGuard* getGuardById(GuardId) const = 0;
    virtual void* getActionInterface() const = 0;
};
}
