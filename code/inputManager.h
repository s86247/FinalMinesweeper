#include <stdlib.h>
#include <stdbool.h>
#include <notcurses/notcurses.h>
#include <gpm.h>



typedef enum inputType
{
    LEFT,
    RIGHT,
    DOWN,
    UP,
    FLAGGED,
    CLEARED,
    QUIT,
    RESTART,
    NONE
}t_input;

void initializeInput();

t_input get_input();

struct notcurses* getNotCursesRefrence();