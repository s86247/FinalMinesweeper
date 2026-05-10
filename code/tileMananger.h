#include <stdlib.h>
#include <stdbool.h>
#include <notcurses/notcurses.h>
#include "gameManager.h"


typedef enum typeSpace
{
    BLANK,
    HELPER,
    UNSEEN,
    FLAG
}t_space;

typedef struct normalTile
{
    struct ncplane* tilePlane;
    t_space spaceType; 
    int minesAdjacent;
    int numMines;
    bool isMine;
    bool isBlack;
    
}t_tile;

char getTileGraphic(t_tile tile);

uint32_t getTileColor(t_tile tile);


void updateMinesShowing(bool lost);

//int normalFindAdjacent(t_tile tile);


