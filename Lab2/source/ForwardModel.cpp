#include "ForwardModel.H"

ForwardModel::ForwardModel()
{}

void ForwardModel::Step(GameState& game_state, Action& player1Action, Action& player2Action)
{
    // Do the motion. If action == 0 remains at the same position
	if      (player1Action.IsUp())    game_state.player1_row    -= 1;
	else if (player1Action.IsRight()) game_state.player1_column += 1;
	else if (player1Action.IsDown())  game_state.player1_row    += 1;
	else if (player1Action.IsLeft())  game_state.player1_column -= 1;


	if      (player2Action.IsUp())    game_state.player2_row    -= 1;
	else if (player2Action.IsRight()) game_state.player2_column += 1;
	else if (player2Action.IsDown())  game_state.player2_row    += 1;
	else if (player2Action.IsLeft())  game_state.player2_column -= 1;
	
	// check limits
	if (game_state.player1_row    < 0)  game_state.player1_row    = 0;
	if (game_state.player1_row    > 23) game_state.player1_row    = 23;
	if (game_state.player1_column < 0)  game_state.player1_column = 0;
	if (game_state.player1_column > 31) game_state.player1_column = 31;

	if (game_state.player2_row    < 0)  game_state.player2_row    = 0;
	if (game_state.player2_row    > 23) game_state.player2_row    = 23;
	if (game_state.player2_column < 0)  game_state.player2_column = 0;
	if (game_state.player2_column > 31) game_state.player2_column = 31;

    // Detect if the player collects the coin
    if (game_state.player1_row == game_state.coin_row && game_state.player1_column == game_state.coin_column)
        game_state.coin_collected = true;
}