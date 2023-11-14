#ifndef SOURCE_GAMESTATE_H
#define SOURCE_GAMESTATE_H
#include <nds.h>
#include <vector>

class GameState
{
public:
    int collected_coins;
    int pacman_row;
    int pacman_col;
    int **world;      // It is a matrix of 24 rows and 32 columns

    GameState();
    ~GameState();
    void Reset();

    int  GetTileID(int row, int col);   // Return the tile ID in this position
    bool IsPath(int row, int col);     // Return true if the position is a place where Pacman can be
    bool IsCoin(int row, int col);     // Return true if there is a coin in that position
    void RemoveCoin(int row, int col); // Remove the coin from the world
    bool IsTerminal();
};
#endif
