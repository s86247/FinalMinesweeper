#include <stdlib.h>
#include <stdbool.h>
#include <notcurses/notcurses.h>
#include <gpm.h>


#include "gameManager.h"
#include "mineMananger.h"


void initializeInput();

int get_input();

struct notcurses* getNotCursesRefrence();

void updateSelectedTile(t_tile tile);
