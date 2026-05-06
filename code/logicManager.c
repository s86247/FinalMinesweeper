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
    numMinesLeft = 0;
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
        numMinesLeft = generateMines();
        getSelectedTile()->spaceType = BLANK;
    }
    str[10]= (char)(numMinesLeft/10)+'0';
    str[11]= (char)(numMinesLeft%10)+'0';
    ncplane_putstr_yx(statsPlane, 0, 0, str);
}