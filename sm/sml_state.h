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

#include <map>
#include <string>
#include <vector>

#include "sml_eventhandlerexpression.h"

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
    void evaluateEventExpression(EventHandlerExpression& exp, IStateMachineInstance& sm);
    std::string _name;
    std::map<EventId, std::vector<EventHandlerExpression>> _events;
    std::vector<ActionId> _entryActions;
    std::vector<ActionId> _exitActions;
};
}  // namespace sml
