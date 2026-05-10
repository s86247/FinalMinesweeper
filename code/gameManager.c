#include <stdlib.h>
#include <stdbool.h>
#include "gameManager.h"

/*Let the mine manager determine the total number of mi*/


t_state universalGameState;
t_mode universalGameMode;
t_size universalGameSize;

int customGameRows;
int customGameCols;
int customGameMines;


void setGameState(t_state state)
{
    universalGameState = state;
}

t_state getGameState()
{
    return universalGameState;
}

void setGameMode(t_mode mode)
{
    universalGameMode = mode;
}

t_mode getGameMode()
{
    return universalGameMode;
}

void setGameSize(t_size size)
{
    universalGameSize = size;
}
int getGameSize(bool isRow)
{
    if(isRow)
    {
        switch (universalGameSize)
        {
        case SMALL:
            return 9;
        case NORMAL:
            return 16;
        case LARGE:
            return 30;
        case CUSTOM:
            return customGameCols;
        default:
            return 0;
        }
    }
    else
    {
        switch (universalGameSize)
        {
        case SMALL:
            return 9;
        case NORMAL:
            return 16;
        case LARGE:
            return 16;
        case CUSTOM:
            return customGameCols;
        default:
            return 0;
        }
    }   
}

t_size getUniversalGameSize()
{
    return universalGameSize;
}


int getTotalMineCount()
{
    switch (universalGameSize)
    {
        case SMALL:
            return 10;
        case NORMAL:
            return 40;
        case LARGE:
            return 99;
        case CUSTOM:
            return customGameMines;
        default:
            break;
    }
}
void setCustomParams(int row, int col, int mines)
{
    customGameRows = row;
    customGameCols = col;
    customGameMines = mines;
}