#include <stdlib.h>
#include <stdbool.h>
#include <notcurses/notcurses.h>


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
    bool isMine;
}t_tile;

char getTileGraphic(t_tile tile);

uint32_t getTileColor(t_tile tile);


void updateMinesShowing(bool lost);

//int normalFindAdjacent(t_tile tile);


