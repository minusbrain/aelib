#pragma once

class ActionMock {
public:
	MOCK_METHOD0(action1, void());
	MOCK_METHOD0(action2, void());
	MOCK_METHOD0(action3, void());
	MOCK_METHOD0(action4, void());
    MOCK_METHOD0(action5, void()); 
    MOCK_METHOD0(guard1, bool());
};
