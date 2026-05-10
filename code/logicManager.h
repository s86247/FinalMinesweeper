#include <stdlib.h>
#include <stdbool.h>
#include<time.h>
#include <notcurses/notcurses.h>

#include "boardManager.h"

void initializeLogic();

void affectTile(t_input input);

void gameOver();

void reveal(int rowOffset, int colOffset);

void updateStats(time_t start, time_t end);

void resetScreen();

void setIsTimeRelated(bool is);