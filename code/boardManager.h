#include <stdlib.h>
#include <stdbool.h>
#include <notcurses/notcurses.h>

#include "gameManager.h"
#include "tileMananger.h"
#include "inputManager.h"

extern t_tile **gameBoard;

extern t_tile selectedTile;

void initializeBoard();

void freeBoard();

void printBoard();

struct ncplane* getStandardPlane();

void moveCursor(t_input movement);

void updateSelectedTile(t_tile tile);

int generateMines();

int getTileDistance(int row1, int col1, int row2, int col2);

t_tile getTileRelative(int row, int col);

void changeTileSpaceTypeRelative(int row, int col, t_space space);

void setMinesAdjacentRelative(int row, int col, int mines);

bool isInBounds(int row, int col);

int takeMineCount();