/** @file 
 *@author Tristan Risi, 900367080
 *@date 5/10/2026
*/

#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <notcurses/notcurses.h>

#include"boardManager.h"


//The standard plane for the program
struct ncplane *stdplane = NULL;
//The double array acting as the board
t_tile **gameBoard;
//The equivalent of a NULL tile that getTileRelative() can return if the index was out of bounds
t_tile emptyTile;
//The currently selectedTile
t_tile selectedTile;
//The row and col of the selectedTile
int selectedRow, selectedCol;
//A bool that helps keep the logic for chess board printing in printBoard()
bool blackTile = true;
//An int that stores the real mine count for double mine
int realNumMines;


//I wanna give credit to Vincente he taught me I could manipluate the cell paramters to make the grid 
//square and later place the cells according to the i and j of the double for loop.
//Before that I was storing a tile cell and then a blank cell to make the grid square.
//Sets up the cell paramaters for each tile on the board
struct ncplane_options tileOptions = {
    .rows = 1,
    .cols = 2,
};


void setStandardPlane()
{
    stdplane = notcurses_stdplane(getNotCursesRefrence());
}

struct ncplane* getStandardPlane()
{
    return stdplane;
}

void initializeBoard() 
{
    //Sets up realNumMines to be used if needed
    if(getGameMode() == DOUBLEMINE){realNumMines=0;}
    //If not the realNumMines will be what is expected for the board size
    else{realNumMines = getTotalMineCount();}

    //Sets up the emptyTile as a null tile
    emptyTile.minesAdjacent = -1;
    emptyTile.isMine = false;

    //Allocating the space for gameBoard according to the gameSize
    gameBoard = (t_tile **)malloc(getGameSize(true) * sizeof(t_tile));
    for(int i = 0; i < getGameSize(true);i++)
    {
    gameBoard[i] = (t_tile *)malloc(getGameSize(false) * sizeof(t_tile));
    }

    //a temp variable allowing rows to move down smoothly incase its chess variant
    bool startingTile = blackTile;

    //Double for loop going through every board space to initalize the tiles
    for(int i = 0; i < getGameSize(true); i++)
    {
        for(int j = 0; j < getGameSize(false); j++)
        {
            //The tile cell placement code Vinny helped me with
            tileOptions.y = i + 2;
            tileOptions.x = j*2 + 6;
            gameBoard[i][j].tilePlane = ncplane_create(stdplane,  &tileOptions);
            ncplane_set_fg_rgb8(gameBoard[i][j].tilePlane, 0,0,0);
            gameBoard[i][j].minesAdjacent = 0;
            gameBoard[i][j].spaceType = UNSEEN;
            gameBoard[i][j].isMine = false;
            gameBoard[i][j].numMines = 0;
            //if the game mode is Chess it sets the isBlack flipflopping starting on black
            if(getGameMode() == CHESS)
            {
                gameBoard[i][j].isBlack = blackTile;
                blackTile = !blackTile;
            }
        }
        //Again if its chess it uses the temp variable and sets it opposite to smoothly move down a row
        if(getGameMode() == CHESS)
        {
            blackTile = !startingTile;
            startingTile = !startingTile;
        }
    }

    //Makes sure the selected tile plane is Null so it can be passed into updateSelectedTile
    selectedTile.tilePlane = NULL;
    //Takes the midpoint of the board to pass in as the row and col of the selected tile
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
            //Makes sure the selected tile's color doesnt change then sets all other tiles to their correct color
            if(!(i==selectedRow && j==selectedCol)){ncplane_set_fg_rgb(gameBoard[i][j].tilePlane, getTileColor(gameBoard[i][j]));}
        }
    }
}




void moveCursor(t_input movement)
{
    //Changes the row or column of the selected based on the given movement
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
    //Then makes sure its in bounds and redirects accordingly
    if (selectedRow<0){selectedRow++;}
    else if (selectedCol<0){selectedCol++;}
    else if(selectedRow>=getGameSize(true)){selectedRow--;}
    else if(selectedCol>=getGameSize(false)){selectedCol--;}
    //Finally if its in bounds it sets the new selected tile as the new row and col
    else{updateSelectedTile(gameBoard[selectedRow][selectedCol]);}
}


void updateSelectedTile(t_tile tile)
{
    //Changes the color of the old tile back to its correct color
    if(selectedTile.tilePlane != NULL) {ncplane_set_fg_rgb(selectedTile.tilePlane, getTileColor(selectedTile)); }
    //Sets the selected tile as the new tile
    selectedTile = tile;
    //Changes the color to a white highlight if its not chess and a red highlight if it is
    if(getGameMode() == CHESS){ncplane_set_fg_rgb8(selectedTile.tilePlane, 150,0,0);}
    else{ncplane_set_fg_rgb8(selectedTile.tilePlane, 255,255,255);}
}

int generateMines()
{
    //Makes and sets a seed according to both the time and identity of the function call
    srand(time(NULL) ^ getpid());

    //Temp variable tracking how many mines are placed
    int minesPlaced = 0;
    //Places mines until at expected amount
    while(minesPlaced < getTotalMineCount())
    {
        for(int i = 0; i < getGameSize(true); i++)
        {
            for(int j = 0; j < getGameSize(false); j++)
            {
                int random = rand() % 10;
                //Has a 10% chance for random to equal 3, then it also can't be the first place cleared, and it can't be within 1 tile unless size is custom
                if(random == 3 && !gameBoard[i][j].isMine && !(i== selectedRow && j == selectedCol)&&(getUniversalGameSize() == CUSTOM || getTileDistance(i,j,selectedRow,selectedCol) >1))
                {
                    //If all of those conditons are met a mine is placed
                    gameBoard[i][j].isMine = true;
                    minesPlaced ++;
                    //if its double mine there's a 20% another mine is placed and the int num mines of tile is increased without increasing minesplaced.
                    if(getGameMode() == DOUBLEMINE)
                    {
                        while(true)
                        {
                            realNumMines++;
                            gameBoard[i][j].numMines++;
                            random = rand() % 10;
                            if(random < 8){break;}
                        }
                    }
                    //When enough mines are placed return;
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
                //If the tile is both a mine and is flagged then the mineCount goes up by 1
                if(gameBoard[i][j].isMine && gameBoard[i][j].spaceType == FLAG){mineCount++;}
            }
        }
    return mineCount;
}

int getRealMines()
{
    return realNumMines;
}