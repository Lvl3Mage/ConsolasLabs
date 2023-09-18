#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "<vector>"
class GameState
{
public:
	int player1_row;
	int player1_column;
	int player2_row;
	int player2_column;
	vector<int> coinRows;
	vector<int> coinColumns;
	
	GameState();
	void Reset();
	bool IsTerminal();
};

#endif