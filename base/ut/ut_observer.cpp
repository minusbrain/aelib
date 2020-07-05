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
