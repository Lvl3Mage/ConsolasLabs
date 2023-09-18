#include "GameState.H"
#include <cstdlib> // for rand() and srand() functions
#include <ctime> // for time() function to seed rand()
GameState::GameState()
{ }
int randSeed = 0;
int* GenRandomPosition(){
	int* coords = new int[2];
	// Seed the random number generator with the current time
	srand(randSeed);
	randSeed++;
	int N = 23;
	coords[0] = std::rand() % (N + 1);
	coords[1] = std::rand() % (N + 1);
	return coords;
}
void GameState::AddCoin(){
	int* coords = GenRandomPosition();
	coinRows.push_back(coords[0]);
	coinColumns.push_back(coords[1]);
	delete coords;
}
void GameState::RemoveCoin(int index){
	coinRows.erase(coinRows.begin() + index);
	coinColumns.erase(coinColumns.begin() + index);
}
void GameState::Reset()
{
	int* coordsPlayer1 = GenRandomPosition();
	int* coordsPlayer2 = GenRandomPosition();
	player1_row     = coordsPlayer1[0];
	player1_column  = coordsPlayer1[1];
	delete coordsPlayer1;
	player2_row     = coordsPlayer2[0];
	player2_column  = coordsPlayer2[1];
	delete coordsPlayer2;
	coinRows.clear();
	coinColumns.clear();
	for(int i = 0; i < 5; i++){
		AddCoin();
	}
	player1CoinsCollected = 0;
	player2CoinsCollected = 0;
}
	
bool GameState::IsTerminal()
{
	return coinRows.size() == 0;
}
int GameState::IntersectsCoin(int x, int y){
	for(int i = 0; i < coinRows.size(); i++){
		if(y == coinRows[i] && x == coinColumns[i]){
			return i;
		}
	}
	return -1;
}