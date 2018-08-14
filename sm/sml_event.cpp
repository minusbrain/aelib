#include <aelib/sm/sml_event.h>

namespace sml {

	Event::Event(const std::string& name) : _name(name)
	{
	}

	Event::Event() : _name("")
	{
	}

	Event::~Event()
	{
	}

	const std::string& Event::getName() const {
		return _name;
	}
}