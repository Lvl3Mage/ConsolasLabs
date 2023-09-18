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
	player1CoinCollected = false;
	player2CoinCollected = false;
}
	
bool GameState::IsTerminal()
{
	if (player1CoinCollected || player2CoinCollected) return true;
	return false;
}