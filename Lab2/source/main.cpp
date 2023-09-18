#include <nds.h>
#include <stdio.h>
#include "GameState.H"
#include "ForwardModel.H"

// Show the player and coin position
void ShowWorld(GameState& game_state)
{
	consoleClear();
	iprintf("\x1b[%d;%dHX", game_state.player1_row, game_state.player1_column);
	iprintf("\x1b[%d;%dH$", game_state.player2_row, game_state.player2_column);
	if (!(game_state.player1CoinCollected || game_state.player2CoinCollected))
		iprintf("\x1b[%d;%dH0", game_state.coin_row, game_state.coin_column);
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
	Action action1;
	Action action2;
	if (key & KEY_UP)    action1.SetUp();
	if (key & KEY_RIGHT) action1.SetRight();
	if (key & KEY_DOWN)  action1.SetDown();
	if (key & KEY_LEFT)  action1.SetLeft();

	if (key & KEY_X)    action2.SetUp();
	if (key & KEY_Y) action2.SetRight();
	if (key & KEY_B)  action2.SetDown();
	if (key & KEY_A)  action2.SetLeft();
	forward_model.Step(game_state, action1, action2);
}

// -----------------------------------
// Main program
// -----------------------------------
int main()
{
	GameState    game_state;
	ForwardModel forward_model;
	// PrintConsole pantalla_sup, pantalla_inf;
	// videoSetMode    (MODE_0_2D);
	// videoSetModeSub (MODE_0_2D);

	// consoleInit(&pantalla_sup,
	// 	3,
	// 	BgType_Text4bpp,
	// 	BgSize_T_256x256,
	// 	31,
	// 	0,
	// 	true,
	// 	true );

	// consoleInit(&pantalla_inf,
	// 	3,
	// 	BgType_Text4bpp,
	// 	BgSize_T_256x256,
	// 	31,
	// 	0,
	// 	false,
	// 	true );
		
	SetUp(game_state);
	while(1)
	{
		if (!game_state.IsTerminal())
			Update(game_state, forward_model);
		else
			ShowWorld(game_state);
		swiWaitForVBlank();
	}
}
