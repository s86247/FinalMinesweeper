#include <stdlib.h>
#include <stdbool.h>
#include "tileMananger.h"

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
        if(tile.isMine){return 'M';}
        else{return '#';}
    default:
        break;
    }
    return NULL;
}

/*int normalFindAdjacent(t_tile tile)
{
    
}*/


