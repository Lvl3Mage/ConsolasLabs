#ifndef FORWARDMODEL_H
#define FORWARDMODEL_H

#include "Action.H"
#include "GameState.H"

class ForwardModel
{
public:
	ForwardModel();
	void Step(GameState& game_state, Action& action, int worldTime);
};

#endif