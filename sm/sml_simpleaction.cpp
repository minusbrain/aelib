#include <aelib/sm/sml_simpleaction.h>

namespace sml {
	SimpleAction::SimpleAction(std::function<void(void)> functionToCall) : IAction(), _functionToCall(functionToCall)
	{}

	SimpleAction::SimpleAction() : _functionToCall()
	{}

	SimpleAction::~SimpleAction()
	{}

    void SimpleAction::execute(void*) {
		_functionToCall();
	}
}
