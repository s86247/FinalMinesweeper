#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <notcurses/notcurses.h>

#include "inputManager.h"

struct notcurses *nc = NULL;
t_tile selectedTile;


void initializeInput()
{
    
    struct notcurses_options opts = {.flags = NCOPTION_SUPPRESS_BANNERS};
    nc = notcurses_init(&opts, NULL);
    selectedTile.tilePlane = NULL;
}

int get_input()
{
    ncinput ni;
    uint32_t key = notcurses_get_blocking(nc, &ni);
    if (ni.evtype == NCTYPE_PRESS) {
        switch (ni.id) {
            case NCKEY_LEFT:
            case 'a':
                return 1;
            case NCKEY_RIGHT:
            case 'd':
                return 2;
            case NCKEY_DOWN:
            case 's':
                return 3;
            case NCKEY_UP:
            case 'w':
                return 4;
            case NCKEY_ESC:
                return -1;
            default:
                return 0;
        }
    }
    else{return 0;}
}

struct notcurses* getNotCursesRefrence()
{
    return nc;
}

void updateSelectedTile(t_tile tile)
{
    if(selectedTile.tilePlane != NULL) {ncplane_set_fg_rgb8(selectedTile.tilePlane, 0,0,0); }
    selectedTile = tile;
    ncplane_set_fg_rgb8(selectedTile.tilePlane, 255,255,255);
}
