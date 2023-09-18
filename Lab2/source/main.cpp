#include <nds.h>
#include <stdio.h>
#include "GameState.H"
#include "ForwardModel.H"

// Show the player and coin position
void ShowWorld(GameState& game_state, PrintConsole& screenTop, PrintConsole& screenBottom)
{
	consoleClear();

	consoleSelect(&screenBottom);
	iprintf("\x1b[%d;%dHX", game_state.player1_row, game_state.player1_column);
	iprintf("\x1b[%d;%dH$", game_state.player2_row, game_state.player2_column);
	consoleSelect(&screenTop);
	iprintf("\x1b[%d;%dHPlayer 1: %d", 18, 2, game_state.player1CoinsCollected);
	iprintf("\x1b[%d;%dHPlayer 2: %d", 18, 20, game_state.player2CoinsCollected);
	if (!game_state.IsTerminal()){
		consoleSelect(&screenBottom);
		for(int i = 0; i < game_state.coinRows.size();i++){
			iprintf("\x1b[%d;%dH0", game_state.coinRows[i], game_state.coinColumns[i]);
		}
	}
	else{
		consoleSelect(&screenTop);
		if(game_state.player1CoinsCollected > game_state.player2CoinsCollected){
			iprintf("\x1b[%d;%dHPlayer 1 wins!", 12, 10);
		}
		else if(game_state.player1CoinsCollected < game_state.player2CoinsCollected){
			iprintf("\x1b[%d;%dHPlayer 2 wins!", 12, 10);

		}
		else{
			iprintf("\x1b[%d;%dHDraw!", 12, 16);
		}
	}
}

// It is run just once at the beginning
void SetUp(GameState& game_state)
{
	consoleDemoInit();
	game_state.Reset();
}

// It is run each iteration
void Update(GameState& game_state, ForwardModel& forward_model, PrintConsole& screenTop, PrintConsole& screenBottom)
{
	u32 key;
	ShowWorld(game_state, screenTop, screenBottom);
	scanKeys();
	key = keysDown();
	Action action1;
	if (key & KEY_UP)    action1.SetUp();
	if (key & KEY_RIGHT) action1.SetRight();
	if (key & KEY_DOWN)  action1.SetDown();
	if (key & KEY_LEFT)  action1.SetLeft();

	Action action2;
	if (key & KEY_X)     action2.SetUp();
	if (key & KEY_Y)     action2.SetRight();
	if (key & KEY_B)     action2.SetDown();
	if (key & KEY_A)     action2.SetLeft();
	forward_model.Step(game_state, action1, action2);
}

// -----------------------------------
// Main program
// -----------------------------------

int main()
{
	GameState    game_state;
	game_state.Reset();
	ForwardModel forward_model;
	PrintConsole screenTop, screenBottom;
	videoSetMode    (MODE_0_2D);
	videoSetModeSub (MODE_0_2D);

	consoleInit(&screenTop,
		3,
		BgType_Text4bpp,
		BgSize_T_256x256,
		31,
		0,
		true,
		true );

	consoleInit(&screenBottom,
		3,
		BgType_Text4bpp,
		BgSize_T_256x256,
		31,
		0,
		false,
		true );
		
	SetUp(game_state);
	while(1)
	{
		if (!game_state.IsTerminal())
			Update(game_state, forward_model, screenTop, screenBottom);
		else{
			scanKeys();
			u32 key = keysDown();
			if(key & KEY_START){
				game_state.Reset();
			}
			ShowWorld(game_state, screenTop, screenBottom);
		}
		swiWaitForVBlank();
	}
}
