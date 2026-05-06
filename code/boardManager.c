#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <notcurses/notcurses.h>

#include"boardManager.h"


t_tile **gameBoard;

t_tile selectedTile;
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
            gameBoard[i][j].isMine = false;
            gameBoard[i][j].hasFlag = false;
        }
    }

    selectedTile.tilePlane = NULL;
    selectedRow = getGameSize(true)/2;
    selectedCol = getGameSize(false)/2;
    updateSelectedTile(gameBoard[selectedRow][selectedCol]);
    
}

void freeBoard()
{
    for (int i = 0; i < getGameSize(true); i++) { free(gameBoard[i]); }
    free(gameBoard);
}

t_tile* getTileAt(int row, int col)
{
    return &gameBoard[row][col];
}

void printBoard()
{
    for(int i = 0; i < getGameSize(true); i++)
    {
        for(int j = 0; j < getGameSize(false); j++)
        {
            char str[2]; 
            str[0] = getTileGraphic(gameBoard[i][j]);
            str[1] = '\0'; 
            ncplane_putstr_yx(gameBoard[i][j].tilePlane, 0, 0, str);
        }
    }
}

struct ncplane* getStandardPlane()
{
    return stdplane;
}

t_tile* getSelectedTile()
{
    return &selectedTile;
}

void moveCursor(t_input movement)
{
    switch (movement)
    {
    case LEFT:
        selectedCol--;
        break;
    case RIGHT:
        selectedCol++;
        break;
    case DOWN:
        selectedRow++;
        break;
    case UP:
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


void updateSelectedTile(t_tile tile)
{
    if(selectedTile.tilePlane != NULL) {ncplane_set_fg_rgb8(selectedTile.tilePlane, 0,0,0); }
    selectedTile = tile;
    ncplane_set_fg_rgb8(selectedTile.tilePlane, 255,255,255);
}

int generateMines()
{
    unsigned int seed = ((unsigned int)time(NULL) ^ (unsigned int)getpid());
    srand(seed^ (unsigned int)getpid());
    int minesPlaced = 0;
    while(minesPlaced < getTotalMineCount())
    {
        for(int i = 0; i < getGameSize(true); i++)
        {
            for(int j = 0; j < getGameSize(false); j++)
            {
                int random = rand() % 10;
                if(random == 3 && !gameBoard[i][j].isMine && !(i== selectedRow && j == selectedCol))
                {
                    gameBoard[i][j].isMine = true;
                    minesPlaced ++;
                    if(minesPlaced==getTotalMineCount()){return minesPlaced;}
                }
            }
        }
    }
    return minesPlaced;
}