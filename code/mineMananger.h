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
    int row, col;
    int minesAdjacent;
    bool isMine;
    bool hasFlag;
}t_tile;

char getTileGraphic(t_tile tile);

int normalFindAdjacent(t_tile tile);


