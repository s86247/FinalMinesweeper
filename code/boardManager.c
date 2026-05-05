#include <stdlib.h>
#include <stdbool.h>
#include <notcurses/notcurses.h>

#include"boardManager.h"


t_tile **gameBoard;
struct ncplane *stdplane = NULL;


void initializeBoard() 
{
    stdplane = notcurses_stdplane(getNotCursesRefrence());
    ncplane_cursor_move_yx(stdplane, 5, 5);
    ncplane_set_bg_rgb8(stdplane, 150,150,150);


    gameBoard = (t_tile **)malloc(getGameSize(true) * sizeof(t_tile *));
    
    for (int i = 0; i < getGameSize(true); i++) 
    {
        gameBoard[i] = (t_tile *)malloc(getGameSize(false) * sizeof(t_tile));
    }

    for(int i = 0; i < getGameSize(true); i++)
    {
        for(int j = 0; j < getGameSize(false); j++)
        {
            gameBoard[i][j].spaceType = UNSEEN;
            gameBoard[i][j].hasFlag = false;
        }
    }
    
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
            ncplane_printf_yx(stdplane, i, j*2, "%c ", getTileGraphic(gameBoard[i][j]));
        }
    }
    notcurses_render(getNotCursesRefrence());
}

struct ncplane* getStandardPlane()
{
    return stdplane;
}