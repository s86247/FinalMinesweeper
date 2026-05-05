#include <stdlib.h>
#include <stdbool.h>

typedef enum typeSpace
{
    BLANK,
    HELPER,
    UNSEEN,
    FLAG
}t_space;

typedef struct normalTile
{
    t_space spaceType; 
    int minesAdjacent;
    bool isMine;
    bool hasFlag;
}t_tile;

char getTileGraphic(t_tile tile);

int normalFindAdjacent(t_tile tile);


