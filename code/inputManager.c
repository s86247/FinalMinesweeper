/** @file 
 *@author Tristan Risi, 900367080
 *@date 5/10/2026
*/

#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <notcurses/notcurses.h>

#include "inputManager.h"

//The universal NotCurses instance
struct notcurses *nc = NULL;


void initializeInput()
{
    //intalizing NotCurses making sure it doesnt give a run time summary
    struct notcurses_options opts = {.flags = NCOPTION_SUPPRESS_BANNERS};
    nc = notcurses_init(&opts, NULL);
}

t_input get_input()
{
    //Setting up an ncinput
    ncinput ni;
    //and waiting for it to get filled from the main instance of NotCurse
    uint32_t key = notcurses_get_blocking(nc, &ni);

    //Makes sure the input flag was a press and not a release or drag
    if (ni.evtype == NCTYPE_PRESS) {
        //Switch statment returning the appropriate t_input based on the key pressed
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
            case 'r':
                return RESTART;
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

