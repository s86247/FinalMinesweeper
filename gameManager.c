#include <stdlib.h>
#include <stdbool.h>
#include "gameManager.h"

t_mode universalGameMode;
t_size universalGameSize;

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
void getGameSize(t_size size, bool isRow)
{
    if(isRow)
    {
        switch (size)
        {
        case SMALL:
            return 9;
        case NORMAL:
            return 16;
        case LARGE:
            return 30;
        default:
            break;
        }
    }
    else
    {
        switch (size)
        {
        case SMALL:
            return 9;
        case NORMAL:
            return 16;
        case LARGE:
            return 16;
        default:
            break;
        }
    }   
}