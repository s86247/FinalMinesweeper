#include <stdlib.h>
#include <stdbool.h>
#include <notcurses/notcurses.h>
#include "mineMananger.h"
#include "gameManager.h"


t_tile **gameBoard;

void initializeBoard() 
{
    gameBoard = (t_tile **)malloc(getGameSize(true) * sizeof(t_tile *));
    
    for (int i = 0; i < getGameSize(true); i++) 
    {
        gameBoard[i] = (t_tile *)malloc(getGameSize(false) * sizeof(t_tile));
    }
}

void freeBoard()
{
    for (int i = 0; i < 20; i++) { free(gameBoard[i]); }
    free(gameBoard);
}
