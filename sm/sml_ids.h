#pragma once
namespace sml {

	class Id {
	public:
		Id(unsigned int id);
		unsigned int getRawId() const;
	private:
		unsigned int _id;
	};

	bool operator<(const Id& lhs, const Id& rhs);

	typedef Id EventId;
	typedef Id ActionId;
	typedef Id GuardId;
	typedef Id StateId;
}
