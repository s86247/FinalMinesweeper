#include <stdlib.h>
#include <stdbool.h>
#include <notcurses/notcurses.h>
#include "logicManager.h"


int numMinesLeft;
bool firstSpaceCleared;
char str[13] ={"Num Mines:00\0"};

struct ncplane *statsPlane = NULL;

struct ncplane_options statsOptions = {
    .rows = 2,
    .cols = 15,
};

void initializeLogic()
{
    numMinesLeft = getTotalMineCount();
    firstSpaceCleared = false;
    statsPlane = ncplane_create(getStandardPlane(),  &statsOptions);
    ncplane_move_yx(statsPlane, 0, getGameSize(false)*2);
    ncplane_putstr_yx(statsPlane, 0, 0, str);
}

void affectTile(t_input input)
{
    if(input == CLEARED && !firstSpaceCleared)
    {
        firstSpaceCleared = true;
        generateMines();
    }
    if(input == CLEARED && numMinesLeft >0)
    {
        if(getTileRelative(0,0).isMine){setGameState(LOST);}
        else if(getTileRelative(0,0).spaceType == UNSEEN){reveal(0,0);}
    }
    else if(input == FLAGGED && getTileRelative(0,0).spaceType != FLAGGED)
    {
        changeTileSpaceTypeRelative(0,0, FLAGGED);
        numMinesLeft --;
    }
    else
    {
        return;
    }
    
    if(numMinesLeft < 1)
    {
        if(getTotalMineCount == takeMineCount()) {setGameState(WON);}
    }
    str[10]= (char)(numMinesLeft/10)+'0';
    str[11]= (char)(numMinesLeft%10)+'0';
    ncplane_putstr_yx(statsPlane, 0, 0, str);
}


void reveal(int rowOffset, int colOffset)
{
    int numMinesAdj = 0;
    for(int i=-1; i<2; i++)
    {
        for(int j=-1; j<2; j++)
        {
            if(!(i==rowOffset && j == colOffset))
            {
                t_tile emtpyTileChecker = getTileRelative(rowOffset + i,colOffset+j);
                if(emtpyTileChecker.minesAdjacent == -1){continue;}
                else if(emtpyTileChecker.isMine){numMinesAdj++;}
            }
        }
    }
    if(numMinesAdj>0)
    {
        changeTileSpaceTypeRelative(rowOffset,colOffset,HELPER);
        setMinesAdjacentRelative(rowOffset,colOffset,numMinesAdj);
    }
    else
    {
        changeTileSpaceTypeRelative(rowOffset,colOffset,BLANK);
        for(int i=-1; i<2; i++)
        {
            for(int j=-1; j<2; j++)
            {
                if(!(i==rowOffset && j == colOffset))
                {
                    t_tile emtpyTileChecker = getTileRelative(rowOffset + i,colOffset+j);
                    if(emtpyTileChecker.minesAdjacent == -1){continue;}
                    else if(emtpyTileChecker.spaceType!=BLANK&&!emtpyTileChecker.isMine){reveal(rowOffset + i,colOffset+j);}
                }
            }
        }
    }
}
