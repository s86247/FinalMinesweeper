#include <stdlib.h>
#include <stdbool.h>
#include <notcurses/notcurses.h>
#include "mineMananger.h"
#include "gameManager.h"
#include "inputManager.h"


void initializeBoard();

void freeBoard();

t_tile getTileAt(int row, int col);

void printBoard();

struct ncplane* getStandardPlane();