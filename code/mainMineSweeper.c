#include <stdlib.h>
#include <stdbool.h>
#include <notcurses/notcurses.h>


#include "logicManager.h"



int main()
{
    setGameMode(STANDARD);
    setGameSize(LARGE);
    initializeInput();
    initializeBoard();
    initializeLogic();
    while(true)
    {
        printBoard();
        notcurses_render(getNotCursesRefrence());
        t_input input = get_input();
        if(input == NONE)
        {
            continue;
        }
        else if(input == FLAGGED || input == CLEARED)
        {
            affectTile(input);
        }
        else if(input == QUIT)
        {
            ncplane_erase(getStandardPlane());
            notcurses_stop(getNotCursesRefrence());
            freeBoard();
            return 0;
        }
        else if(input == LEFT || input == DOWN ||input == UP ||input == RIGHT)
        {
            moveCursor(input);
        }
        else{return 1;}
    }
   // printf("COMPILED");
}
