/**
 * @author     Andreas Evers
 *
 * @copyright  Copyright © 2021 Andreas Evers
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

namespace base {

template <typename T_callback>
class scope_guard {
   public:
    scope_guard(T_callback guard) : _guard(guard) {}
    scope_guard() = delete;

    ~scope_guard() { _guard(); }

   private:
    T_callback _guard;
};

template <typename T_callback>
class armed_scope_guard {
   public:
    armed_scope_guard(T_callback guard) : _guard(guard) {}
    armed_scope_guard() = delete;

    ~armed_scope_guard() {
        if (armed) _guard();
    }

    void disarm() { armed = false; }

   private:
    T_callback _guard;
    bool armed = true;
};

}  // namespace base