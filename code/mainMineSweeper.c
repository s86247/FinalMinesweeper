#include <stdlib.h>
#include <stdbool.h>
#include <notcurses/notcurses.h>


#include "logicManager.h"

void freeGame();


int main()
{
    setGameState(PLAYING);
    setGameMode(STANDARD);
    setGameSize(SMALL);
    initializeInput();
    initializeBoard();
    initializeLogic();
    while(true)
    {
        if(getGameState() == WON)
        {
            ncplane_printf_yx(getStandardPlane(),40,40,"YOU WONNNN");
        }
        else if(getGameState() == LOST)
        {
            ncplane_printf_yx(getStandardPlane(),40,40,"YOU LOST");
        }
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
            freeGame();
        }
        else if(input == LEFT || input == DOWN ||input == UP ||input == RIGHT)
        {
            moveCursor(input);
        }
        else{return 1;}
    }
   // printf("COMPILED");
}

void freeGame()
{
    ncplane_erase(getStandardPlane());
    notcurses_stop(getNotCursesRefrence());
    freeBoard();
    return 0;
}