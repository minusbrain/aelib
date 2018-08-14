#include <sm/sml_simpleguard.h>

namespace sml {

SimpleGuard::SimpleGuard(std::function<bool(void)> guardToCall,
                         bool expectedResult)
  : _guardToCall(guardToCall), _expectedResult(expectedResult) {}

SimpleGuard::SimpleGuard() : _guardToCall(), _expectedResult(false) {}

SimpleGuard::~SimpleGuard() {}

bool SimpleGuard::check(void*) { return (_guardToCall() == _expectedResult); }
}
