#pragma once

namespace sml {
    class IAction
    {
    public:
        virtual ~IAction() {};

        virtual void execute(void* ptr = nullptr) = 0;
    };
}
