#pragma once
#include <functional>
#include <sm/sml_if_action.h>

namespace sml {
class SimpleAction : public IAction {
  public:
    SimpleAction();
    SimpleAction(std::function<void(void)>);
    virtual ~SimpleAction();

    virtual void execute(void* ptr = nullptr);

  private:
    std::function<void(void)> _functionToCall;
};
}
