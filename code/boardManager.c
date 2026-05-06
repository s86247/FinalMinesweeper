#include <stdlib.h>
#include <stdbool.h>
#include <notcurses/notcurses.h>

#include"boardManager.h"


t_tile **gameBoard;
int selectedRow, selectedCol;

struct ncplane *stdplane = NULL;
struct ncplane_options tileOptions = {
    .rows = 1,
    .cols = 2,
};

void initializeBoard() 
{
    stdplane = notcurses_stdplane(getNotCursesRefrence());
    
    gameBoard = (t_tile **)malloc(getGameSize(true) * sizeof(t_tile));
    for(int i = 0; i < getGameSize(true);i++)
    {
    gameBoard[i] = (t_tile *)malloc(getGameSize(false) * sizeof(t_tile));
    }

    for(int i = 0; i < getGameSize(true); i++)
    {
        for(int j = 0; j < getGameSize(false); j++)
        {
            tileOptions.y = i;
            tileOptions.x = j*2;

            gameBoard[i][j].tilePlane = ncplane_create(stdplane,  &tileOptions);
            ncplane_set_fg_rgb8(gameBoard[i][j].tilePlane, 0,0,0);
            gameBoard[i][j].spaceType = UNSEEN;
            gameBoard[i][j].hasFlag = false;
        }
    }
    selectedRow = getGameSize(true)/2;
    selectedCol = getGameSize(false)/2;
    updateSelectedTile(gameBoard[selectedRow][selectedCol]);
    
}

void freeBoard()
{
    for (int i = 0; i < getGameSize(true); i++) { free(gameBoard[i]); }
    free(gameBoard);
}

t_tile getTileAt(int row, int col)
{
    return gameBoard[row][col];
}

void printBoard()
{
    for(int i = 0; i < getGameSize(true); i++)
    {
        for(int j = 0; j < getGameSize(false); j++)
        {
            ncplane_putstr_yx(gameBoard[i][j].tilePlane, 0, 0, "#");
        }
    }
    notcurses_render(getNotCursesRefrence());
}

struct ncplane* getStandardPlane()
{
    return stdplane;
}

void moveCursor(int movement)
{
    switch (movement)
    {
    case -1:
        break;
    case 1:
        selectedCol--;
        break;
    case 2:
        selectedCol++;
        break;
    case 3:
        selectedRow++;
        break;
    case 4:
        selectedRow--;
        break;
    default:
        break;
    }
    if (selectedRow<0){selectedRow++;}
    else if (selectedCol<0){selectedCol++;}
    else if(selectedRow>=getGameSize(true)){selectedRow--;}
    else if(selectedCol>=getGameSize(false)){selectedCol--;}
    else{updateSelectedTile(gameBoard[selectedRow][selectedCol]);}
}