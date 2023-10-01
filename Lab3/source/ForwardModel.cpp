#include "ForwardModel.H"
#include <cstdlib> // for rand() and srand() functions

ForwardModel::ForwardModel()
{}
int GenRandomRoom(int seed){
    srand(seed);
    return (std::rand() % (13)) + 1;
}
void Fight(GameState& game_state){
    if(!game_state.foundSword){
        game_state.lives --;
    }
    else{
        game_state.enemyDead = true;
    }
}
void ForwardModel::Step(GameState& game_state, Action& action, int worldTime)
{
    
    if(worldTime >= game_state.enemyMoveTime){
        game_state.enemyMoveTime += 2;
        game_state.enemyRoom = GenRandomRoom(worldTime);
        if(game_state.enemyRoom == game_state.room && action.IsEmpty()){
            Fight(game_state);
        }
    }
    if (game_state.room == 1)
    {
        if      (action.IsUp())    { game_state.room = 2; }
        else if (action.IsRight()) { game_state.room = 3; }
        else if (action.IsDown())  { game_state.room = 4; }
        else if (action.IsLeft())  { game_state.room = 5; }
    }
    else if (game_state.room == 2)
    {
        if      (action.IsRight()) { game_state.room = 6; }
        else if (action.IsDown())  { game_state.room = 1; }
        else if (action.IsLeft())  { game_state.room = 12; }
    }
    else if (game_state.room == 3)
    {
        if      (action.IsUp())    { game_state.room = 6; }
        else if (action.IsRight()) { game_state.room = 7; }
        else if (action.IsDown())  { game_state.room = 5; }
        else if (action.IsLeft())  { game_state.room = 1; }
    }
    else if (game_state.room == 4)
    {
        if      (action.IsUp())    { game_state.room = 1; }
        else if (action.IsRight()) { game_state.room = 10; }
        else if (action.IsLeft())  { game_state.room = 8; }
        else if (action.IsDown())  { game_state.room = 13; }
    }
    else if (game_state.room == 5)
    {
        if      (action.IsRight()) { game_state.room = 1; }
        else if (action.IsDown())  { game_state.room = 8; }
        else if (action.IsLeft())  { game_state.room = 3; }
        else if (action.IsOpen() && !game_state.key_room5_collected)
        {
            game_state.keys_collected     += 1;
            game_state.key_room5_collected = true;
        }
    }
    else if (game_state.room == 6)
    {
        if      (action.IsUp())    { game_state.room = 7; }
        else if (action.IsRight()) { game_state.room = 9; }
        else if (action.IsDown())  { game_state.room = 3; }
        else if (action.IsLeft())  { game_state.room = 2; }
    }
    else if (game_state.room == 7)
    {
        if      (action.IsUp())    { game_state.room = 6; }
        else if (action.IsDown())  { game_state.room = 9; }
        else if (action.IsLeft())  { game_state.room = 3; }
        else if (action.IsOpen() && !game_state.key_room7_collected)
        {
            game_state.keys_collected     += 1;
            game_state.key_room7_collected = true;
        }
    }
    else if (game_state.room == 8)
    {
        if      (action.IsUp())    { game_state.room = 5; }
        else if (action.IsLeft()) { game_state.room = 12; }
        else if (action.IsRight()) { game_state.room = 4; }
        else if (action.IsDown() && game_state.exit_open)
        { game_state.room = 11;        }
        else if (action.IsOpen() && game_state.keys_collected >= 2 && !game_state.exit_open)
        { game_state.exit_open = true; }
    }
    else if (game_state.room == 9)
    {
        if      (action.IsUp())    { game_state.room = 7; }
        else if (action.IsRight()) { game_state.room = 6; }
        else if (action.IsLeft())  { game_state.room = 10; }
        else if (action.IsDown())  { game_state.room = 13; }
    }
    else if (game_state.room == 10)
    {
        if      (action.IsRight()) { game_state.room = 9; }
        else if (action.IsLeft())  { game_state.room = 4; }
    }
    else if (game_state.room == 12)
    {
        if      (action.IsRight()) { game_state.room = 8; }
        else if (action.IsLeft())  { game_state.room = 2; }
    }
    else if (game_state.room == 13)
    {
        if      (action.IsRight()) { game_state.room = 9; }
        else if (action.IsLeft())  { game_state.room = 4; }
    }
    if(game_state.room == 13){
        game_state.foundSword = true;
    }
    if(!action.IsEmpty()){
        if(game_state.enemyRoom == game_state.room){
            Fight(game_state);
        }
    }
}