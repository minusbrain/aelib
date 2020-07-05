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
#include <functional>
#include <map>
#include <string>

namespace base
{
/**
 * @brief      Registry pattern template
 *
 * The registry pattern implemented here can be used to offer
 * a dynamic instantiation of a subclass of type T identified
 * by a string. Sub-classes can register themselves by providing
 * a string identifier (e.g. their classname) and a factory function
 * of type CREATOR. Clients can then get new instances of subclasses
 * just by calling the createObject function and providing the
 * string indentifier.
 *
 * Example usage
 * @code
 * class MyBaseClass {};
 * class ASubClass: public MyBaseClass {};
 *
 * auto& reg = Registry<MyBaseClass, std::function<MyBaseClass*(int)>::getInstance();
 *
 * // Registration
 * reg.registerClass("ASubClass", [](int value) -> MyBaseClass* { return new ASubClass();
 * });
 *
 * // Instantiation without any hard dependency to type ASubClass
 * // In case no class with string identifier "ASubClass" registered
 * // nullptr is returned
 * auto a = reg.createObject("ASubClass");
 *
 * @endcode
 *
 * @tparam     T        Base-class all registered subclasses must
 *                      be derived from
 * @tparam     CREATOR  Callable type that returns a T* and takes
 *                      whatever arguments the CREATORs need
 */
template <class T, class... PARAMS>
class Registry
{
    typedef std::function<T*(PARAMS...)> Creator;
    typedef std::map<std::string, Creator> Creators;

   public:
    // Get singleton instance of Registry<T, CREATOR>
    static Registry& getInstance()
    {
        static Registry instance;  // Guaranteed to be destroyed.
                                   // Instantiated on first use.
        return instance;
    }

    // No copying or assigning
    Registry(Registry const&) = delete;
    void operator=(Registry const&) = delete;

    // Register a factory function under a given string identifier
    void registerClass(const std::string& className, const Creator& creator)
    {
        // Insert or replace
        _creators[className] = creator;
    }

    // Unregister a previously registerd string identifier / factory function
    void unregisterClass(const std::string& className)
    {
        // Erases class with classname. Fails silently in case className not in map
        _creators.erase(className);
    }

    // Check if a factory function is registered under the provided string identifier
    bool isClassRegistered(const std::string& className) const
    {
        return getRegisteredCreator(className) != nullptr;
    }

    // Instantiate an object of class identfied by given string identifier
    T* createObject(const std::string& className, PARAMS... params)
    {
        Creator* creator = getRegisteredCreator(className);

        return (creator != nullptr) ? (*creator)(params...) : nullptr;
    }

   private:
    Registry() {}
    Creators _creators;

    Creator* getRegisteredCreator(const std::string& className)
    {
        auto it = _creators.find(className);
        return (it != _creators.end()) ? &(it->second) : nullptr;
    }
};
}  // namespace base
