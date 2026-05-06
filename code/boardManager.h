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

t_tile* getTileAt(int row, int col);

void printBoard();

struct ncplane* getStandardPlane();

t_tile* getSelectedTile();

void moveCursor(t_input movement);

void updateSelectedTile(t_tile tile);

int generateMines();
