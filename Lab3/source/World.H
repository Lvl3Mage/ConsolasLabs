#ifndef WORLD_H
#define WORLD_H
#include "Action.H"
#include <string>
#include <list>
using namespace std;

class World
{
public:
    World();
    int          GetStartRoom();
    bool         IsExit(int room);
    list<Action> GetActionsForRoom(int room, bool open_action);
    string       GetTextForRoom(int room);
};

#endif