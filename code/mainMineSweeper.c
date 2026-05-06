#include <stdlib.h>
#include <stdbool.h>
#include <notcurses/notcurses.h>


#include "boardManager.h"



int main()
{
    setGameMode(STANDARD);
    setGameSize(NORMAL);
    initializeInput();
    initializeBoard();

    while(true)
    {
        printBoard();
        int input = get_input();
        if(input == -1)
        {
            ncplane_erase(getStandardPlane());
            notcurses_stop(getNotCursesRefrence());
            freeBoard();
            return 0;
        }
        else
        {
            moveCursor(input);
        }
    }
   // printf("COMPILED");
}
