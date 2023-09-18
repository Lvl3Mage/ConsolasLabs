#ifndef GAMESTATE_H
#define GAMESTATE_H

class GameState
{
public:
	int player1_row;
	int player1_column;
	int player2_row;
	int player2_column;
	int coin_row;
	int coin_column;
	bool player1CoinCollected;
	bool player2CoinCollected;
	
	GameState();
	void Reset();
	bool IsTerminal();
};

#endif