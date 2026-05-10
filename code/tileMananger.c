#include <stdlib.h>
#include <stdbool.h>
#include "tileMananger.h"

bool haveLost = false;

char getTileGraphic(t_tile tile)
{
    switch (tile.spaceType)
    {
    case FLAG:
        return 'F';
    case BLANK:
        return '-';
    case HELPER:
        return (char)(tile.minesAdjacent)+'0'; 
    case UNSEEN:
        if(tile.isMine && haveLost){return 'M';}
        else{return '#';}
    default:
        break;
    }
    return NULL;
}

uint32_t getTileColor(t_tile tile)
{
    uint8_t r = 0, g = 11, b = 11;
    if(tile.spaceType == UNSEEN || tile.spaceType == BLANK)
    {
        r = 0;
        g = 0;
        b = 0;
    }
    else if(tile.spaceType == FLAG){b=255;}
    else if(tile.spaceType==HELPER)
    {
        if(r<240){r = 50 * tile.minesAdjacent;}
        if(g>10){g = 255 - (50 * tile.minesAdjacent);}
        if(b>10){b = 155 - (50 * tile.minesAdjacent);}
    }

    uint32_t color = ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
    return color;
}

void updateMinesShowing(bool lost)
{
    haveLost = lost;
}

/*int normalFindAdjacent(t_tile tile)
{
    
}*/


