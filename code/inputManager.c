#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <notcurses/notcurses.h>
#include <gpm.h>

#include "inputManager.h"

struct notcurses *nc = NULL;

Gpm_Connect conn;

void initializeInput()
{
    
    struct notcurses_options opts = {.flags = NCOPTION_SUPPRESS_BANNERS};

    nc = notcurses_init(&opts, NULL);
    

    //Tells the primary event mask to only listen for movement and clicks
    conn.eventMask = GPM_DOWN | GPM_DRAG;
    //Tells the default mask to handle everything else
    conn.defaultMask = ~conn.eventMask;  
    //Sets up an intger to pass into not curses equal to the primary event mask

    int notcurses_mice_enable(struct notcurses* n,unsigned  primaryEventMask);
}

int get_input()
{
    ncinput ni;
    uint32_t key = notcurses_get_blocking(nc, &ni);

    switch (ni.id) {
        case NCKEY_BUTTON1:
            return 1;
        case NCKEY_BUTTON2:
            return 2;
        case NCKEY_TAB:
            return 3;
        case NCKEY_LALT:
            return 4;
        default:
            return 0;
    }
}

struct notcurses* getNotCursesRefrence()
{
    return nc;
}



