#include "GameState.H"

GameState::GameState()
{
}
	
void GameState::Reset()
{
	room                = world.GetStartRoom();
    keys_collected      = 0;
    exit_open           = false;
    key_room5_collected = false;
    key_room7_collected = false;
}
	
bool GameState::IsTerminal()
{
	if (room == world.IsExit(room)) return true;
    if(lives == 0) return true;
	return false;
}

std::list<Action> GameState::GetActionsForActualRoom()
{
    bool open_action = false;

    // we only show the open action in room 8 if we have not collected all the keys
    // We only show the open action in rooms 5 and 7 if the keys have not been collected yet
    if (room == 8 && keys_collected >= 2)  open_action = true;
    if (room == 5 && !key_room5_collected) open_action = true;
    if (room == 7 && !key_room7_collected) open_action = true;

    return world.GetActionsForRoom(room, open_action);
}

std::string GameState::GetTextForActualRoom()
{
    return world.GetTextForRoom(room);
}