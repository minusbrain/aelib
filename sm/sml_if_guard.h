#pragma once

namespace sml {
    class IGuard
    {
    public:
        virtual ~IGuard() {};

        virtual bool check(void* ptr = nullptr) = 0;
    };
}
