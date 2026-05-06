#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <notcurses/notcurses.h>

#include "inputManager.h"

struct notcurses *nc = NULL;


void initializeInput()
{
    struct notcurses_options opts = {.flags = NCOPTION_SUPPRESS_BANNERS};
    nc = notcurses_init(&opts, NULL);
}

t_input get_input()
{
    ncinput ni;
    uint32_t key = notcurses_get_blocking(nc, &ni);
    if (ni.evtype == NCTYPE_PRESS) {
        switch (ni.id) {
            case NCKEY_LEFT:
            case 'a':
                return LEFT;
            case NCKEY_RIGHT:
            case 'd':
                return RIGHT;
            case NCKEY_DOWN:
            case 's':
                return DOWN;
            case NCKEY_UP:
            case 'w':
                return UP;
            case 'c':
            case 'z':
                return CLEARED;
            case 'f':
            case 'x':
                return FLAGGED;
            case NCKEY_ESC:
                return QUIT;
            default:
                return NONE;
        }
    }
    else{return NONE;}
}

struct notcurses* getNotCursesRefrence()
{
    return nc;
}

