#include "ForwardModel.h"

void ForwardModel::Step(GameState &gs, Action &action)
{
    int row = gs.pacman_row;
    int col = gs.pacman_col;

    if (action.IsUp() && (row-1 >= 0))
    {
        if (gs.IsPath(row-1, col))
        {
            gs.pacman_row -= 1;
            if (gs.IsCoin(row-1, col))
                gs.RemoveCoin(row-1, col);
        }
    }
    else if (action.IsRight())
    {
        if ((col+1 == 32) && (row == 11))
        {
            gs.pacman_row = 11;
            gs.pacman_col = 0;
            if (gs.IsCoin(11, 0))
                gs.RemoveCoin(11, 0);
        }
        else if (col+1 < 32)
        {
            if (gs.IsPath(row, col + 1))
            {
                gs.pacman_col += 1;
                if (gs.IsCoin(row, col + 1))
                    gs.RemoveCoin(row, col + 1);
            }
        }
    }
    else if (action.IsDown() && (row+1 < 24))
    {
        if (gs.IsPath(row+1, col))
        {
            gs.pacman_row += 1;
            if (gs.IsCoin(row+1, col))
                gs.RemoveCoin(row+1, col);
        }
    }
    else if (action.IsLeft())
    {
        if ((col-1 == -1) && (row == 11))
        {
            gs.pacman_row = 11;
            gs.pacman_col = 31;
            if (gs.IsCoin(11, 31))
                gs.RemoveCoin(11, 31);
        }
        else if (col-1 >= 0)
        {
            if (gs.IsPath(row, col-1))
            {
                gs.pacman_col -= 1;
                if (gs.IsCoin(row, col - 1))
                    gs.RemoveCoin(row, col - 1);
            }
        }
    }
}
