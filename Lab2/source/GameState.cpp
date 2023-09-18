#include "GameState.H"
#include <cstdlib> // for rand() and srand() functions
#include <ctime> // for time() function to seed rand()
GameState::GameState()
{ }
int* GenRandomPosition(){
	int* coords = new int[2];
	// Seed the random number generator with the current time
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	int N = 23;
	coords[0] = std::rand() % (N + 1);
	coords[1] = std::rand() % (N + 1);
	return coords;
}
void GameState::Reset()
{
	player1_row     = 0;
	player1_column  = 0;
	player2_row     = 0;
	player2_column  = 0;
	int* coords = GenRandomPosition();
	coin_row       = coords[0];
	coin_column    = coords[1];
	player1CoinCollected = false;
	player2CoinCollected = false;
}
	
bool GameState::IsTerminal()
{
	if (player1CoinCollected || player2CoinCollected) return true;
	return false;
}