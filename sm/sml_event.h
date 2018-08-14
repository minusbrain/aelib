#pragma once
#include <string>

namespace sml {
	class Event
	{
	public:
		Event();
		Event(const std::string& name);
		const std::string& getName() const;
		~Event();
	private:
		std::string _name;
	};
}
