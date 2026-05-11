/** @file 
 *@author Tristan Risi, 900367080
 *@date 5/10/2026
*/

#include <stdlib.h>
#include <stdbool.h>
#include "tileMananger.h"

//The common boolean letting the program know to show mines
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

    //If the game mode is chess color is determined by if its black or white
    if(getGameMode() == CHESS)
    {
        if(tile.isBlack)
        {
            r=0;
            g=0;
            b=0;
        }
        else
        {
            r=255;
            g=255;
            b=255;
        }
    }
    //If its blank or unseen the color is automatically black
    else if(tile.spaceType == UNSEEN || tile.spaceType == BLANK)
    {
        r = 0;
        g = 0;
        b = 0;
    }
    //Flags are set to blue
    else if(tile.spaceType == FLAG){b=255;}
    //Then for HELPER tiles theres an algorithim that determines color
    else if(tile.spaceType==HELPER)
    {
        if(r<240){r = 40 + 40 * tile.minesAdjacent;}
        if(g>10){g = 255 - (40 * tile.minesAdjacent);}
        if(b>10){b = 155 - (50 * tile.minesAdjacent);}
    }
    //Converts the r g b values into uint32_t
    uint32_t color = ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
    return color;
}

void updateMinesShowing(bool lost)
{
    haveLost = lost;
}

