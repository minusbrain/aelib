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

#include <sm/sml_ids.h>

#include <string>
#include <vector>

namespace sml
{
class IAction;
class IGuard;

class IStateMachineInstance
{
   public:
    virtual ~IStateMachineInstance(){};

    virtual std::string getCurrentStatename() const = 0;
    virtual void onEvent(const std::string& eventName) = 0;
    virtual void onEvent(const EventId& eventId) = 0;

    virtual void transitionTo(StateId stateId, const std::vector<ActionId>& actions) = 0;

    virtual IAction* getActionById(ActionId) const = 0;
    virtual IGuard* getGuardById(GuardId) const = 0;
    virtual void* getActionInterface() const = 0;
};
}  // namespace sml
