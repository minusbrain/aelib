#pragma once
#include <string>

class ScopedTrace {
   public:
    ScopedTrace(std::string name) : _name(name) {}

   private:
    std::string _name;
};

#define TRC_SCOPED(name) \
    ScopedTrace __traceobj { name }

#define TRC_WARN(text) ;
#define TRC_INFO(text) ;
#define TRC_ERROR(text) ;