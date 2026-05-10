#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <notcurses/notcurses.h>


#include "logicManager.h"

void freeGame();
void setMenuSelected(int numSelected);
void mainMenu(int index);
void customSetUp();

int smallBestTime = 31;
int normalBestTime = 192;
int largeBestTime = 689;


bool isCustom = false;
bool menuDone = false;


struct ncplane *menuButtons[6];

struct ncplane_options menuOptions = {
    .rows = 1,
    .cols = 150,
};



int main()
{
    mainMenu(0);
    if(!menuDone){return 0;}
    while(true)
    {
        setStandardPlane();
        setGameState(PLAYING);
        initializeBoard();
        initializeLogic();
        time_t startTime = time(NULL);
        while(true)
        {
            time_t endTime = time(NULL);
            if(getGameMode() == TIME)
            {
                int totalSeconds = (int)difftime(endTime, startTime);
                int timeToBeat;
                switch (getUniversalGameSize())
                {
                case SMALL:
                    if(getGameState() == WON){smallBestTime = totalSeconds;}
                    timeToBeat = smallBestTime;
                    break;
                case NORMAL:
                    if(getGameState() == WON){normalBestTime = totalSeconds;}
                    timeToBeat = normalBestTime;
                    break;
                case LARGE:
                    if(getGameState() == WON){largeBestTime = totalSeconds;}
                    timeToBeat = largeBestTime;
                    break;
                default:
                    break;
                }
                if(totalSeconds>=timeToBeat)
                {
                    setGameState(LOST);
                    setIsTimeRelated(true);
                }
            }
            updateStats(startTime, endTime);
            printBoard();
            notcurses_render(getNotCursesRefrence());
            t_input input = get_input();
            
            if(input == RESTART)
            {
                resetScreen();
                setGameState(PLAYING);
                updateMinesShowing(false);
                break;
            }
            else if(input == QUIT)
            {
                freeGame();
                return 0;
            }
            else if(getGameState() != PLAYING){updateMinesShowing(true);}
            else if(input == NONE)
            {
                continue;
            }
            else if(input == FLAGGED || input == CLEARED)
            {
                affectTile(input);
            }
            
            else if(input == LEFT || input == DOWN ||input == UP ||input == RIGHT)
            {
                moveCursor(input);
            }
            else{return 1;}
        }
    }
   // printf("COMPILED");
}

void freeGame()
{
    ncplane_erase(getStandardPlane());
    notcurses_stop(getNotCursesRefrence());
    if(menuDone){freeBoard();}
}

void mainMenu(int index)
{
    int numOptions = 0;
    int optionChoice = 0;
    t_input menuChoice;

    initializeInput();
    setStandardPlane();
    
    for(int i = 0; i<6; i++)
    {
        menuOptions.y = i;
        menuButtons[i] = ncplane_create(getStandardPlane(),  &menuOptions);
    }
     
    while(true)
    {
        switch (index)
        {
        case 0:
            ncplane_putstr_yx(menuButtons[0],0,0,"WELCOME TO MINESWEEPER");
            ncplane_putstr_yx(menuButtons[1],0,0,"GAME CONTROLS:");
            ncplane_putstr_yx(menuButtons[2],0,0,"Press Z or C to clear tiles, press F to flag, press R to reset, use Arrow Keys or WSAD to move cursor, and ESC to quit");
            ncplane_putstr_yx(menuButtons[3],0,0,"MENU CONTROLS:");
            ncplane_putstr_yx(menuButtons[4],0,0,"Press Z or C confirm, press F to go back, use Arrow Keys or WSAD to move cursor");
            ncplane_putstr_yx(menuButtons[5],0,0,"Please confirm to continue");
            notcurses_render(getNotCursesRefrence());
            menuChoice = get_input();
            break;
        case 1:
            numOptions = 5;
            ncplane_putstr_yx(menuButtons[0],0,0,"PLEASE SELECT A GAMEMODE:");
            ncplane_putstr_yx(menuButtons[1],0,0,"STANDARD:");
            ncplane_putstr_yx(menuButtons[2],0,0,"CHESS");
            ncplane_putstr_yx(menuButtons[3],0,0,"LIAR:");
            ncplane_putstr_yx(menuButtons[4],0,0,"DOUBLE BOMB");
            ncplane_putstr_yx(menuButtons[5],0,0,"TIME TRIAL");
            setMenuSelected(optionChoice);
            notcurses_render(getNotCursesRefrence());
            menuChoice = get_input();
            if(menuChoice == CLEARED){setGameMode(optionChoice);}
            break;
        case 2:
            if(getGameMode() != TIME){numOptions = 4;}
            else{numOptions = 3;}
            ncplane_putstr_yx(menuButtons[0],0,0,"PLEASE SELECT A GAME SIZE:");
            ncplane_putstr_yx(menuButtons[1],0,0,"SMALL:");
            ncplane_putstr_yx(menuButtons[2],0,0,"NORMAL");
            ncplane_putstr_yx(menuButtons[3],0,0,"LARGE:");
            if(getGameMode() != TIME){ncplane_putstr_yx(menuButtons[4],0,0,"CUSTOM");}
            setMenuSelected(optionChoice);
            notcurses_render(getNotCursesRefrence());
            menuChoice = get_input();
            if(menuChoice == CLEARED && optionChoice!=3){setGameSize(optionChoice);}
            else if(menuChoice == CLEARED && optionChoice ==3){isCustom = true;}
            break;
        default:
            break;
        }
        for(int i = 0; i<6; i++){ncplane_erase(menuButtons[i]);}

        if(isCustom)
        {
            customSetUp();
            setGameSize(CUSTOM);
        }
        
        if(menuChoice == FLAGGED && index > 0)
        {
            optionChoice = 0;
            index--;
        }
        else if(menuChoice == CLEARED) 
        {
            optionChoice = 0;
            index++;
        }
        else if(menuChoice== DOWN && optionChoice+1 < numOptions){optionChoice++;}
        else if(menuChoice== UP && optionChoice-1 >= 0){optionChoice--;}
        else if(menuChoice == QUIT){freeGame(); return;}
        if(index>=3)
        {
            ncplane_erase(getStandardPlane());
            menuDone = true;
            return;
        }
    }
} 

void setMenuSelected(int numSelected)
{
    for(int i = 0; i<6; i++)
    {
        if(i-1 == numSelected){ncplane_set_fg_rgb8(menuButtons[i], 255,255,255);}
        else{ncplane_set_fg_rgb8(menuButtons[i], 0,0,0);}
    }
}

void customSetUp()
{
    int param[3];
    char setupString[3][22] = {"Number of Rows: 04","Number of Cols: 04","Number of Mine:001" };
    struct ncplane* selectionScreen = ncplane_create(getStandardPlane(), &menuOptions);
    for(int i =0; i<3; i++)
    {
        int numThing = 4;
        int maxThing;
        if(i==2){maxThing = (param[0]*param[1])/2;}
        else{maxThing = 99;}
        while(true)
        {
            ncplane_putstr(selectionScreen, setupString[i]);
            notcurses_render(getNotCursesRefrence());
            t_input input = get_input();
            if(input == UP && numThing < maxThing){numThing++;}
            else if(input == DOWN && numThing-1>3){numThing--;}
            else if(input == CLEARED){param[i] = numThing; break;}
            int temp = numThing;
            setupString[i][15] = ' ';
            setupString[i][16] = ' ';
            setupString[i][17] = ' '; 
            for(int j = 17; temp >0; j--) 
            {
                setupString[i][j] = (char)temp%10+'0';
                temp = temp/10;
            }
            ncplane_erase(selectionScreen);
        }
    }
    ncplane_erase(selectionScreen);
    setCustomParams(param[0], param[1], param[2]);
}