#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <notcurses/notcurses.h>
#include <gpm.h>

#include "inputManager.h"

static struct notcurses *nc = NULL;
static struct ncplane *stdplane = NULL;

Gpm_Connect conn;

void initializeInput()
{
    
    struct notcurses_options opts = {.flags = NCOPTION_SUPPRESS_BANNERS};

    nc = notcurses_init(&opts, NULL);
    stdplane = notcurses_stdplane(nc);

    //Tells the primary event mask to only listen for movement and clicks
    conn.eventMask = GPM_DOWN | GPM_DRAG;
    //Tells the default mask to handle everything else
    conn.defaultMask = ~conn.eventMask;  
    //Sets up an intger to pass into not curses equal to the primary event mask
    unsigned primaryEventMask = conn.eventMask;

    int notcurses_mice_enable(struct notcurses* n,unsigned  primaryEventMask);
}

int get_input(int *cursor_col) {
    ncinput ni;
    switch (ni.id) {
        case NCKEY_BUTTON1:

            return 1;
        case NCKEY_BUTTON2:
        
        default:
            return 1;
    }
}