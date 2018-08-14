#pragma once
#include <functional>
#include <sm/sml_if_guard.h>

namespace sml {
template <class T_If> class InterfaceGuard : public IGuard {
  public:
    InterfaceGuard(std::function<bool(T_If&)> guardToCall, bool expectedResult);
    virtual ~InterfaceGuard();

    virtual bool check(void* ptr);

  private:
    InterfaceGuard();
    std::function<bool(T_If&)> _functionToCall;
    bool _expectedResult;
};

template <class T_If>
InterfaceGuard<T_If>::InterfaceGuard(std::function<bool(T_If&)> functionToCall,
                                     bool expectedResult)
  : IGuard(), _functionToCall(functionToCall), _expectedResult(expectedResult) {
}

template <class T_If> InterfaceGuard<T_If>::~InterfaceGuard() {}

template <class T_If> bool InterfaceGuard<T_If>::check(void* ptr) {
    T_If* concretePtr = reinterpret_cast<T_If*>(ptr);
    return (_functionToCall(*concretePtr) == _expectedResult);
}
}
