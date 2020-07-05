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
#include <base/observer.h>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

class IMyObserver
{
   public:
    virtual void eventA(int param) = 0;
    virtual void eventB(int param) = 0;

    virtual ~IMyObserver() {}
};

class MySubject : public base::Subject<IMyObserver>
{
   public:
    MySubject() : base::Subject<IMyObserver>() {}
    ~MySubject() {}
    void notifyEventA(int /*param*/)
    { /*observers.eventA(param);*/
    }
    void notifyEventB(int /*param*/)
    { /*observers.eventB(param);*/
    }
};

class MyObserver : public IMyObserver
{
   public:
    MyObserver() : IMyObserver() {}
    virtual void eventA(int /*param*/) {}
    virtual void eventB(int /*param*/) {}

    virtual ~MyObserver() {}
};

class MyMockObserver : public MyObserver
{
   public:
    MyMockObserver() : MyObserver() {}
    MOCK_METHOD1(eventA, void(int));
    MOCK_METHOD1(eventB, void(int));

    virtual ~MyMockObserver() {}
};

TEST(ObserverPattern, OneObserver_notifyEvent_expectCallToObserver)
{
    /*    MySubject subject;
        auto observer1 = new MyMockObserver();
        // auto observer2 = new MyMockObserver();

        EXPECT_CALL(*observer1, eventA(42)).Times(1);
        subject.registerObserver(observer1);
        subject.notifyEventA(42);
        delete observer1;*/
}
