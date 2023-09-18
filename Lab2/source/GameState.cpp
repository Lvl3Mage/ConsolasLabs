#include "GameState.H"

GameState::GameState()
{ }
	
void GameState::Reset()
{
	player1_row     = 0;
	player1_column  = 0;
	player2_row     = 0;
	player2_column  = 0;
	coin_row       = 10;
	coin_column    = 10;
	coin_collected = false;
}
	
bool GameState::IsTerminal()
{
	if (coin_collected) return true;
	return false;
}