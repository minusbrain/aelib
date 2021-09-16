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

#include "sml_if_guard.h"

namespace sml {
template <class T_If>
class InterfaceGuard : public IGuard {
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
InterfaceGuard<T_If>::InterfaceGuard(std::function<bool(T_If&)> functionToCall, bool expectedResult)
    : IGuard(), _functionToCall(functionToCall), _expectedResult(expectedResult) {}

template <class T_If>
InterfaceGuard<T_If>::~InterfaceGuard() {}

template <class T_If>
bool InterfaceGuard<T_If>::check(void* ptr) {
    T_If* concretePtr = reinterpret_cast<T_If*>(ptr);
    return (_functionToCall(*concretePtr) == _expectedResult);
}
}  // namespace sml
