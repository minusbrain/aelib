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
#include <functional>

#include "sml_if_action.h"

namespace sml {
template <class T_If>
class InterfaceAction : public IAction {
   public:
    InterfaceAction(std::function<void(T_If&)> functionToCall);
    virtual ~InterfaceAction();

    virtual void execute(void* ptr);

   private:
    InterfaceAction();
    std::function<void(T_If&)> _functionToCall;
};

template <class T_If>
InterfaceAction<T_If>::InterfaceAction(std::function<void(T_If&)> functionToCall)
    : IAction(), _functionToCall(functionToCall) {}

template <class T_If>
InterfaceAction<T_If>::~InterfaceAction() {}

template <class T_If>
void InterfaceAction<T_If>::execute(void* ptr) {
    T_If* concretePtr = reinterpret_cast<T_If*>(ptr);
    _functionToCall(*concretePtr);
}
}  // namespace sml
