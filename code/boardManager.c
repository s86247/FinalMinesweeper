#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <notcurses/notcurses.h>

#include"boardManager.h"


t_tile **gameBoard;
t_tile emptyTile;
t_tile selectedTile;
int selectedRow, selectedCol;

struct ncplane *stdplane = NULL;
struct ncplane_options tileOptions = {
    .rows = 1,
    .cols = 2,
};

void setStandardPlane()
{
    stdplane = notcurses_stdplane(getNotCursesRefrence());
}

void initializeBoard() 
{
    
    emptyTile.minesAdjacent = -1;
    emptyTile.isMine = false;
    gameBoard = (t_tile **)malloc(getGameSize(true) * sizeof(t_tile));
    for(int i = 0; i < getGameSize(true);i++)
    {
    gameBoard[i] = (t_tile *)malloc(getGameSize(false) * sizeof(t_tile));
    }
    for(int i = 0; i < getGameSize(true); i++)
    {
        for(int j = 0; j < getGameSize(false); j++)
        {
            tileOptions.y = i + 2;
            tileOptions.x = j*2 + 6;

            gameBoard[i][j].tilePlane = ncplane_create(stdplane,  &tileOptions);
            ncplane_set_fg_rgb8(gameBoard[i][j].tilePlane, 0,0,0);
            gameBoard[i][j].minesAdjacent = 0;
            gameBoard[i][j].spaceType = UNSEEN;
            gameBoard[i][j].isMine = false;
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
            if(!(i==selectedRow && j==selectedCol)){ncplane_set_fg_rgb(gameBoard[i][j].tilePlane, getTileColor(gameBoard[i][j]));}
        }
    }
}

struct ncplane* getStandardPlane()
{
    return stdplane;
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
    if(selectedTile.tilePlane != NULL) {ncplane_set_fg_rgb(selectedTile.tilePlane, getTileColor(selectedTile)); }
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
                if(random == 3 && !gameBoard[i][j].isMine && !(i== selectedRow && j == selectedCol)&&(getGameMode() == CUSTOM || getTileDistance(i,j,selectedRow,selectedCol) >1))
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

int getTileDistance(int row1, int col1, int row2, int col2)
{
    return(sqrt(pow(row1 - row2, 2) + pow(col1 - col2, 2)));

}

t_tile getTileRelative(int row, int col)
{
    if(!isInBounds(selectedRow+row,selectedCol+col)){return emptyTile;};
    return gameBoard[selectedRow+row][selectedCol+col];
}

void changeTileSpaceTypeRelative(int row, int col, t_space space)
{
    if(!isInBounds(selectedRow+row,selectedCol+col)){return;}
    else{gameBoard[selectedRow+row][selectedCol+col].spaceType = space;}
}

void setMinesAdjacentRelative(int row, int col, int mines)
{
    if(!isInBounds(selectedRow+row,selectedCol+col)){return;}
    else{gameBoard[selectedRow+row][selectedCol+col].minesAdjacent = mines;}
}

bool isInBounds(int row, int col)
{
    if(row >= getGameSize(true)||col >= getGameSize(false) ||row < 0||col < 0) {return false;}
    else {return true;}
}

int takeMineCount()
{
    int mineCount = 0;
    for(int i = 0; i < getGameSize(true); i++)
        {
            for(int j = 0; j < getGameSize(false); j++)
            {
                if(gameBoard[i][j].isMine && gameBoard[i][j].spaceType == FLAG){mineCount++;}
            }
        }
    return mineCount;
}