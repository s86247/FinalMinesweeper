#include <stdlib.h>
#include <stdbool.h>
#include "mineMananger.h"

char getTileGraphic(t_tile tile)
{
    if(tile.hasFlag)
    {
        return 'F';
    }
    switch (tile.spaceType)
    {
    case BLANK:
        return '-';
    case HELPER:
        return (char)tile.minesAdjacent; 
    case UNSEEN:
        return '#';
    default:
        break;
    }
}

int normalFindAdjacent(t_tile tile)
{
    
}


