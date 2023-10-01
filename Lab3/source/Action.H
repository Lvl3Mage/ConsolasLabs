#ifndef ACTION_H
#define ACTION_H
#include <string>

class Action
{
public:
	int action;
	Action();
	
	bool IsUp();
	bool IsDown();
	bool IsRight();
	bool IsLeft();
    bool IsOpen();
    bool IsEmpty();
	void SetUp();
	void SetRight();
	void SetDown();
	void SetLeft();
    void SetOpen();
    std::string GetText();
};

#endif