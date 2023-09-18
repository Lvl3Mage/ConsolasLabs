#include <vector>
#ifndef GAMESTATE_H
#define GAMESTATE_H
using namespace std;
class GameState
{
	void AddCoin();
public:
	int player1_row;
	int player1_column;
	int player2_row;
	int player2_column;
	vector<int> coinRows;
	vector<int> coinColumns;
	int player1CoinsCollected;
	int player2CoinsCollected;
	
	GameState();
	void Reset();
	bool IsTerminal();
	int IntersectsCoin(int x, int y);
	void RemoveCoin(int index);
};

#endif