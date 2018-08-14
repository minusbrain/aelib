#include <exception>
#include <limits>
#include <sm/sml_ids.h>

namespace sml {
unsigned int Id::getRawId() const { return _id; }

Id::Id(unsigned int id) : _id(id) {}

bool operator<(const Id& lhs, const Id& rhs) {
    return lhs.getRawId() < rhs.getRawId();
}
}
