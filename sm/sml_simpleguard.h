#pragma once
#include <functional>
#include <memory>
#include <aelib/sm/sml_if_guard.h>

namespace sml {

	class SimpleGuard: public IGuard
	{
	public:
		SimpleGuard();
		SimpleGuard(std::function<bool(void)>, bool);
		virtual ~SimpleGuard();

        virtual bool check(void* ptr = nullptr);
	private:
		std::function<bool(void)> _guardToCall;
		bool _expectedResult;
	};
}
