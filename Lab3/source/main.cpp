#include <nds.h>
#include <stdio.h>
#include <time.h>
#include "GameState.H"
#include "ForwardModel.H"


# define TIMER_SPEED ( BUS_CLOCK /1024)
uint ticks = 0;
void RunTimer(){
	ticks += timerElapsed (0) ;
}
int GetSeconds(){
	return ticks/TIMER_SPEED;
}
// Show the player and coin position
void ShowWorld(GameState& game_state)
{
    consoleClear();
    if(game_state.lives == 0){
		iprintf("\x1b[2;1HGame Over");
		return;
    }
	iprintf("\x1b[2;1HYour are in the Room: %d", game_state.room);
    iprintf("\x1b[4;1H%s", game_state.GetTextForActualRoom().c_str());
    iprintf("\x1b[6;1HKeys collected: %d", game_state.keys_collected);

    int c = 8;
    std::list<Action> l_actions = game_state.GetActionsForActualRoom();
    std::list<Action>::iterator it;
    for (it = l_actions.begin(); it!=l_actions.end(); it++)
    {
        std::string s = it->GetText();
        iprintf("\x1b[%d;1H%s", c, s.c_str());
        c += 2;
    }
	iprintf("\x1b[%d;1HLives: %d", c, game_state.lives);
    c+=2;
    if(game_state.foundSword){
	    iprintf("\x1b[%d;1HYou have a sword!", c);
		c+=2;

    }
    if(!game_state.enemyDead){
		iprintf("\x1b[%d;1HEnemy: %d", c, game_state.enemyRoom);
	    c+=2;
	    if(game_state.enemyRoom == game_state.room){
	    	iprintf("\x1b[%d;1HYou see an enemy!", c);
		    c+=2;
	    }

    }
    else{
    	iprintf("\x1b[%d;1HThe enemy is dead!", c);
		c+=2;

    }

}

// It is run just once at the beginning
void SetUp(GameState& game_state)
{
	consoleDemoInit();
	game_state.Reset();
}

// It is run each iteration
void Update(GameState& game_state, ForwardModel& forward_model)
{
	u32 key;
	ShowWorld(game_state);
	scanKeys();
	key = keysDown();
	Action action;
	if (key & KEY_UP)    action.SetUp();
	if (key & KEY_RIGHT) action.SetRight();
	if (key & KEY_DOWN)  action.SetDown();
	if (key & KEY_LEFT)  action.SetLeft();
    if (key & KEY_A)     action.SetOpen();
	forward_model.Step(game_state, action, GetSeconds());
}

// -----------------------------------
// Main program
// -----------------------------------

int main()
{
	GameState    game_state;
	ForwardModel forward_model;

	timerStart (0 , ClockDivider_1024 , 0 , NULL ) ; 
	SetUp(game_state);
	while(1)
	{
		RunTimer();
        if (!game_state.IsTerminal())
		    Update(game_state, forward_model);
        else
            ShowWorld(game_state);
        swiWaitForVBlank();
	}
}
