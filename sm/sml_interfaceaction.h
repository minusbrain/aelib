#pragma once
#include <functional>
#include <sm/sml_if_action.h>

namespace sml {
template <class T_If> class InterfaceAction : public IAction {
  public:
    InterfaceAction(std::function<void(T_If&)> functionToCall);
    virtual ~InterfaceAction();

    virtual void execute(void* ptr);

  private:
    InterfaceAction();
    std::function<void(T_If&)> _functionToCall;
};

template <class T_If>
InterfaceAction<T_If>::InterfaceAction(
  std::function<void(T_If&)> functionToCall)
  : IAction(), _functionToCall(functionToCall) {}

template <class T_If> InterfaceAction<T_If>::~InterfaceAction() {}

template <class T_If> void InterfaceAction<T_If>::execute(void* ptr) {
    T_If* concretePtr = reinterpret_cast<T_If*>(ptr);
    _functionToCall(*concretePtr);
}
}
