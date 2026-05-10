#include <stdlib.h>
#include <stdbool.h>
#include <notcurses/notcurses.h>


#include "logicManager.h"


int numMinesLeft;
bool firstSpaceCleared;
char str[13] ={"Num Mines:00\0"};

struct ncplane *statsPlane = NULL;

struct ncplane_options statsOptions = {
    .rows = 4,
    .cols = 15,
};

void initializeLogic()
{
    numMinesLeft = getTotalMineCount();
    firstSpaceCleared = false;
    statsPlane = ncplane_create(getStandardPlane(),  &statsOptions);
    ncplane_move_yx(statsPlane, 2, getGameSize(false)*2+6);
    str[10]= (char)(numMinesLeft/10)+'0';
    str[11]= (char)(numMinesLeft%10)+'0';
    ncplane_putstr_yx(statsPlane, 0, 0, str);
}

void affectTile(t_input input)
{
    if(input == CLEARED && !firstSpaceCleared)
    {
        firstSpaceCleared = true;
        generateMines();
    }

    if (getTileRelative(0,0).spaceType == BLANK || getTileRelative(0,0).spaceType == HELPER){return;}
    else if(input == CLEARED && numMinesLeft >0)
    {
        if(getTileRelative(0,0).isMine){setGameState(LOST);}
        else if(getTileRelative(0,0).spaceType == UNSEEN){reveal(0,0);}
    }
    else if(input == FLAGGED)
    {
        if( getTileRelative(0,0).spaceType == FLAG)
        {
            changeTileSpaceTypeRelative(0,0, UNSEEN);
            numMinesLeft ++;
        }
        else if(numMinesLeft >0)
        {
            changeTileSpaceTypeRelative(0,0, FLAG);
            numMinesLeft --;
        }
    }
    else
    {
        return;
    }
    
    if(numMinesLeft <= 0)
    {
        if(getTotalMineCount() == takeMineCount()) {setGameState(WON);}
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
        setMinesAdjacentRelative(rowOffset,colOffset,numMinesAdj);
        changeTileSpaceTypeRelative(rowOffset,colOffset,HELPER);
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

void updateStats(time_t start, time_t end)
{
    if(getGameState() == WON){ncplane_putstr_yx(statsPlane, 3, 0, "YOU WON :)");}
    else if(getGameState() == LOST){ncplane_putstr_yx(statsPlane, 3, 0, "YOU LOST :(");}
    else 
    {
        int totalSeconds = (int)difftime(end, start);

        int minutes = totalSeconds / 60;
        int seconds = totalSeconds % 60;

        char timeStr[15]  = "Time: 00:00";

        timeStr[6]= (char)(minutes/10)+'0';
        timeStr[7]= (char)(minutes%10)+'0';

        timeStr[9]= (char)(seconds/10)+'0';
        timeStr[10]= (char)(seconds%10)+'0';

        ncplane_putstr_yx(statsPlane, 2, 0, timeStr);
    }
}

void resetScreen()
{
    ncplane_erase(getStandardPlane());
    ncplane_erase(statsPlane);
}