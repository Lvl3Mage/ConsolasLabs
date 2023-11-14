#ifndef SOURCE_FORWARDMODEL_H
#define SOURCE_FORWARDMODEL_H
#include "GameState.h"
#include "Action.h"

class ForwardModel
{
public:
    ForwardModel() {};
    void Step(GameState &gs, Action &a);
};


#endif
