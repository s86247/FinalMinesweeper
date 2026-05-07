#include <stdlib.h>
#include <stdbool.h>
#include <notcurses/notcurses.h>

#include "boardManager.h"

void initializeLogic();

void affectTile(t_input input);

void gameOver();

void reveal(int rowOffset, int colOffset);