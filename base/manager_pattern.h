/**
 * @author     Andreas Evers
 *
 * @copyright  Copyright © 2020 Andreas Evers
 *
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this
 * software and associated documentation files (the “Software”), to deal in the Software
 * without restriction, including without limitation the rights to use, copy, modify,
 * merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies
 * or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR
 * THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#pragma once
#include <map>
#include <memory>

namespace base {
/**
 * @brief      Container that manages instances of a base class
 *
 * Manager Pattern allows to add, remove and retrieve objects of a given
 * baseclass (or its subclasses). Removing ot retrieving objects works
 * by an ID type that has to support operator< comparison.
 */
template <class T, class ID>
class Manager {
   public:
    using MapType = std::map<ID, std::shared_ptr<T>>;

    // Get singleton instance of MemoryManager<T>
    static Manager& getInstance() {
        static Manager instance;  // Guaranteed to be destroyed.
                                  // Instantiated on first use.
        return instance;
    }

    // No copying or assigning
    Manager(Manager const&) = delete;
    void operator=(Manager const&) = delete;

    bool addObject(const ID& id, T* obj) {
        if (containsObject(id)) return false;
        return _map.emplace(std::make_pair(id, std::shared_ptr<T>(obj))).second;
    }

    bool removeObject(const ID& id) { return _map.erase(id) > 0; }

    bool containsObject(const ID& id) { return _map.find(id) != _map.end(); }

    std::shared_ptr<T> getObject(const ID& id) {
        auto ref = _map.find(id);
        return ref != _map.end() ? (*ref).second : nullptr;
    }

   private:
    Manager() {}

    MapType _map;
};

}  // namespace base