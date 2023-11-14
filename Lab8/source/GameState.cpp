#include "GameState.h"
#include <sstream>
#include <string>

#define TILE_BLACK  0
#define TILE_WALL   1
#define TILE_PACMAN 3
#define TILE_COIN   5

GameState::GameState()
{
    world = new int* [24];
    for (int i=0; i<24; i++)
        world[i] = new int[32];
}

GameState::~GameState()
{
    for (int i=0; i<24; i++)
        delete [] world[i];
    delete world;
}

void GameState::Reset()
{
    collected_coins = 0;
    pacman_row      = 21;
    pacman_col      = 15;

    std::string rows_data[] = {
            "1 1 1 1  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1  1 1 1 1 1",
            "1 5 5 5  5 5 5 5 1 5 5 5 5 5 5 5 5 5 5 5 5 5 1 5 5 5 5  5 5 5 5 1",
            "1 5 1 5  1 5 2 5 1 5 1 1 1 1 1 5 1 1 1 1 1 5 1 5 2 5 1  5 5 1 5 1",
            "1 5 1 5  1 5 5 5 5 5 5 5 1 5 5 5 5 5 1 5 5 5 5 5 5 5 1  5 5 1 5 1",
            "1 5 1 5  1 1 1 5 1 5 1 5 1 5 1 1 1 5 1 5 1 5 1 5 1 1 1  5 5 1 5 1",
            "1 5 5 5  5 5 5 5 1 5 1 5 1 5 1 0 1 5 1 5 1 5 1 5 5 5 5  5 5 5 5 1",
            "1 5 1 5  1 5 2 5 1 5 1 5 1 5 1 1 1 5 1 5 1 5 1 5 2 5 1  5 5 1 5 1",
            "1 5 1 5  1 5 5 5 1 5 1 5 5 5 5 5 5 5 5 5 1 5 1 5 5 5 1  5 5 1 5 1",
            "1 5 1 5  1 1 1 1 1 5 1 5 1 1 1 1 1 1 1 5 1 5 1 1 1 1 1  5 5 1 5 1",
            "1 5 1 5  1 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 1 5 5 5 5 5 1  5 5 1 5 1",
            "1 5 1 5  1 5 1 1 1 1 1 5 1 1 1 0 1 1 1 5 1 1 1 1 1 5 1  5 5 1 5 1",
            "5 5 5 5  5 5 5 5 5 5 5 5 1 0 0 0 0 0 1 5 5 5 5 5 5 5 5  5 5 5 5 5",
            "1 5 1 5  1 5 1 1 1 1 1 5 1 1 1 1 1 1 1 5 1 1 1 1 1 5 1  5 5 1 5 1",
            "1 5 1 5  1 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 1 5 5 5 5 5 1  5 5 1 5 1",
            "1 5 1 5  1 1 1 1 1 5 1 5 1 1 1 1 1 1 1 5 1 5 1 1 1 1 1  5 5 1 5 1",
            "1 5 1 5  1 5 5 5 1 5 1 5 5 5 5 5 5 5 5 5 1 5 1 5 5 5 1  5 5 1 5 1",
            "1 5 1 5  1 5 2 5 1 5 1 5 1 5 1 1 1 5 1 5 1 5 1 5 2 5 1  5 5 1 5 1",
            "1 5 5 5  5 5 5 5 1 5 1 5 1 5 1 0 1 5 1 5 1 5 1 5 5 5 5  5 5 5 5 1",
            "1 5 1 5  1 1 1 5 1 5 1 5 1 5 1 1 1 5 1 5 1 5 1 5 1 1 1  5 5 1 5 1",
            "1 5 1 5  1 5 5 5 5 5 5 5 1 5 5 5 5 5 1 5 5 5 5 5 5 5 1  5 5 1 5 1",
            "1 5 1 5  1 5 2 5 1 5 1 1 1 1 1 5 1 1 1 1 1 5 1 5 2 5 1  5 5 1 5 1",
            "1 5 1 5  1 5 5 5 1 5 5 5 5 5 5 5 5 5 5 5 5 5 1 5 5 5 1  5 5 1 5 1",
            "1 5 5 5  5 5 5 5 1 5 5 5 5 5 5 5 5 5 5 5 5 5 1 5 5 5 5  5 5 5 5 1",
            "1 1 1 1  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1  1 1 1 1 1"};

    // World initialization
    for (int r = 0; r < 24; r++)
    {
        std::istringstream iss(rows_data[r]);
        for (int c = 0; c < 32; c++)
            iss >> world[r][c];
    }
}

int GameState::GetTileID(int row, int column)
{
    return world[row][column];
}

bool GameState::IsPath(int row, int col)
{
    return world[row][col] == TILE_BLACK || world[row][col] == TILE_COIN;
}

bool GameState::IsCoin(int row, int col)
{
    return world[row][col] == TILE_COIN;
}

void GameState::RemoveCoin(int row, int col)
{
    world[row][col] = TILE_BLACK;
    collected_coins += 1;
}

bool GameState::IsTerminal()
{
    return collected_coins == 405;
}