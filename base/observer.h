#pragma once
#include <algorithm>
#include <memory>
#include <vector>

namespace base
{
template <typename T>
class Subject
{
   public:
    Subject() : _smartObservers(), _rawObservers() {}
    ~Subject() {}

    void registerObserver(std::shared_ptr<T>& observer)
    {
        _smartObservers.push_back(observer);
    }
    void registerObserver(T* observer) { _rawObservers.push_back(observer); }

    void unregisterObserver(const std::shared_ptr<T>& observer)
    {
        _smartObservers.erase(
            std::remove_if(_smartObservers.begin(), _smartObservers.end(),
                           [&](const std::weak_ptr<T>& wptr) {
                               return wptr.expired() || wptr.lock() == observer;
                           }),
            _smartObservers.end());
    }
    void unregisterObserver(T* observer) { _rawObservers.erase(observer); }

   private:
    std::vector<std::weak_ptr<T>> _smartObservers;
    std::vector<T*> _rawObservers;
};
}  // namespace base
