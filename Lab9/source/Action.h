#ifndef SOURCE_ACTION_H
#define SOURCE_ACTION_H


class Action
{
public:
    int action;
    Action();

    bool IsUp();
    bool IsDown();
    bool IsRight();
    bool IsLeft();
    void SetUp();
    void SetRight();
    void SetDown();
    void SetLeft();
};

#endif
