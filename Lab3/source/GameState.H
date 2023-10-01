#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "World.H"
#include "Action.H"
#include <string>
#include <list>

class GameState
{
public:
    World world;
	int   room;
    int   keys_collected;
    bool  exit_open;
    bool  key_room5_collected;
    bool  key_room7_collected;
    int enemyRoom = 8;
    int enemyMoveTime = 2;
    int lives = 3;
    bool foundSword = false;
    bool enemyDead = false;
	
	GameState();
	void Reset();
	bool IsTerminal();
    std::list<Action> GetActionsForActualRoom();
    std::string       GetTextForActualRoom();
};

#endif