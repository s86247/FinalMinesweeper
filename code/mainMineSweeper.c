/** @file 
 *@author Tristan Risi, 900367080
 *@date 5/10/2026
*/

#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <notcurses/notcurses.h>

#include "logicManager.h"

/** 
 * @brief Frees all of the memory stored by the game
 */
void freeGame();

/** 
 * @brief The general code handling the main menu and getting the game parameters
 * @param[in] index The index of the menu screen the player is on
 */
void mainMenu(int index);

/** 
 * @brief Highlights the selected option on the menu
 * @param[in] numSelected An int representing the menu selection choice
 */
void setMenuSelected(int numSelected);

/** 
 * @brief A seperate menu allowing the user to configure a custom game
 */
void customSetUp();

//Six planes to store menu choices
struct ncplane *menuButtons[6];
//My personal best times in seconds
int smallBestTime = 31;
int normalBestTime = 192;
int largeBestTime = 689;
//Stores if the player wants a curstom size to help mainMenu()
bool isCustom = false;
//Sees if the menu was completed fully or if it was quit out of
bool menuDone = false;

//Cell size for menuoptions
struct ncplane_options menuOptions = {
    .rows = 1,
    .cols = 100,
};



int main()
{
    //starts the menu at index 0
    mainMenu(0);
    //makes sure the menu wasnt quit out of
    if(!menuDone){return 0;}
    //first while loop that makes sure the games logic and graphics are set up
    while(true)
    {
        setStandardPlane();
        setGameState(PLAYING);
        initializeBoard();
        initializeLogic();
        time_t startTime = time(NULL);
        //second while loop that handles input until the user quits or resets
        while(true)
        {
            time_t endTime = time(NULL);
            //Keeps track of time in relation to PB's if its time trial
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
            //Updates the stats screen with the new time and maybe new game state
            updateStats(startTime, endTime);
            //updates and renders board
            printBoard();
            notcurses_render(getNotCursesRefrence());

            //waits for input
            t_input input = get_input();
            
            //clears game and goes back to first while loop if user restarted game
            if(input == RESTART)
            {
                resetScreen();
                setGameState(PLAYING);
                updateMinesShowing(false);
                break;
            }
            //If the user quit the memory is freed and the program returns
            else if(input == QUIT)
            {
                freeGame();
                return 0;
            }
            //If the user lost or won the mines are shown and they're not allowed to put in any other inputs
            else if(getGameState() != PLAYING){updateMinesShowing(true);}
            //if the input was redundant it continues
            else if(input == NONE) {continue;}
            //if the user tried to affect the selected tile it goes to the logicManager
            else if(input == FLAGGED || input == CLEARED){affectTile(input);}
            //if the user tried to change the selected tile it goes to the boardManager
            else if(input == LEFT || input == DOWN ||input == UP ||input == RIGHT) {moveCursor(input);}
            //if none of these things are true idk what happened and it fails
            else{return 1;}
        }
    }
}

void freeGame()
{
    ncplane_erase(getStandardPlane());
    notcurses_stop(getNotCursesRefrence());
    if(menuDone){freeBoard();}
}

void mainMenu(int index)
{
    //number of options the user could pick
    int numOptions = 0;
    //The option the user picked
    int optionChoice = -1;
    //The input the player gave while on the menu
    t_input menuChoice;

    //Make sure that we can input stuff and get the standard plane
    initializeInput();
    setStandardPlane();
    
    //Create all 6 button planes in relation to the standard plane
    for(int i = 0; i<6; i++)
    {
        menuOptions.y = i;
        menuButtons[i] = ncplane_create(getStandardPlane(),  &menuOptions);
    }
     
    //Hideous loop that mostly renders the text on one of the three menu screens
    //Every loop ends with at least getting user input and rendering
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
            setMenuSelected(optionChoice);
            notcurses_render(getNotCursesRefrence());
            menuChoice = get_input();
            break;
        case 1:
            //Always 5 options
            numOptions = 5;
            ncplane_putstr_yx(menuButtons[0],0,0,"PLEASE SELECT A GAMEMODE:");
            ncplane_putstr_yx(menuButtons[1],0,0,"STANDARD");
            ncplane_putstr_yx(menuButtons[2],0,0,"CHESS");
            ncplane_putstr_yx(menuButtons[3],0,0,"LIAR");
            ncplane_putstr_yx(menuButtons[4],0,0,"DOUBLE BOMB");
            ncplane_putstr_yx(menuButtons[5],0,0,"TIME TRIAL");
            setMenuSelected(optionChoice);
            notcurses_render(getNotCursesRefrence());
            menuChoice = get_input();
            //if the user selected their current choice then the gamemode is the coresponding enum to option choice
            if(menuChoice == CLEARED){setGameMode(optionChoice);}
            break;
        case 2:
            //if its time trial there are only 3 options otherwise 4
            if(getGameMode() != TIME){numOptions = 4;}
            else{numOptions = 3;}
            ncplane_putstr_yx(menuButtons[0],0,0,"PLEASE SELECT A GAME SIZE:");
            ncplane_putstr_yx(menuButtons[1],0,0,"SMALL");
            ncplane_putstr_yx(menuButtons[2],0,0,"NORMAL");
            ncplane_putstr_yx(menuButtons[3],0,0,"LARGE");
            //Another if statment making sure custom doesnt happen with time somehow
            if(getGameMode() != TIME){ncplane_putstr_yx(menuButtons[4],0,0,"CUSTOM");}
            setMenuSelected(optionChoice);
            notcurses_render(getNotCursesRefrence());
            menuChoice = get_input();
            //if the user selected their current choice and its not custom then the game size is the coresponding enum to option choice
            if(menuChoice == CLEARED && optionChoice!=3){setGameSize(optionChoice);}
            //If not isCustom is set to true to allow the collection of custom parameters
            else if(menuChoice == CLEARED && optionChoice ==3){isCustom = true;}
            break;
        default:
            break;
        }
        //clear everything off the menu after getting input
        for(int i = 0; i<6; i++){ncplane_erase(menuButtons[i]);}
        //if its a custom game go straight to getting parameters
        if(isCustom)
        {
            customSetUp();
            setGameSize(CUSTOM);
        }
        //if the user chose to go back and they can let them
        if(menuChoice == FLAGGED && index > 0)
        {
            index--;
            if(index == 0){optionChoice = -1;}
            else{optionChoice = 0;}

        }
        //if the user chose to confirm take them to the next screen
        else if(menuChoice == CLEARED) 
        {
            optionChoice = 0;
            index++;
        }
        //change the option choice based on if they went up or down
        else if(menuChoice== DOWN && optionChoice+1 < numOptions){optionChoice++;}
        else if(menuChoice== UP && optionChoice-1 >= 0){optionChoice--;}
        //if they quit free the game and return
        else if(menuChoice == QUIT){freeGame(); return;}
        //if they're past the last index erase everything and go back
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
        //make all but the selected option black
        if(i-1 == numSelected){ncplane_set_fg_rgb8(menuButtons[i], 255,255,255);}
        //Highlight the selected option with white
        else{ncplane_set_fg_rgb8(menuButtons[i], 0,0,0);}
    }
}

void customSetUp()
{
    //Stores the ints to be passed into setCustomParams()
    int param[3];
    //The three strings that will be cycled through in getting the parameters
    char setupString[3][22] = {"Number of Rows: 04","Number of Cols: 04","Number of Mine:001" };
    //The plane for the selection screen
    struct ncplane* selectionScreen = ncplane_create(getStandardPlane(), &menuOptions);
    for(int i =0; i<3; i++)
    {
        int numThing = 4;
        int maxThing;
        //if getting mines make sure the max is half the product of the rows and cols
        if(i==2){maxThing = (param[0]*param[1])/2;}
        //if not make sure the max is 99
        else{maxThing = 99;}
        while(true)
        {
            //put the appropriate string on screen and render
            ncplane_putstr(selectionScreen, setupString[i]);
            notcurses_render(getNotCursesRefrence());
            //wait for user input
            t_input input = get_input();
            //If its up increase the count of what they want
            if(input == UP && numThing < maxThing){numThing++;}
            //If its down decrease the count of what they want
            else if(input == DOWN && numThing-1>3){numThing--;}
            //if they confirm then set the appropriate parameter to what they wanted
            else if(input == CLEARED){param[i] = numThing; break;}

            //with the new number of what they want update the current string to show it
            int temp = numThing;
            setupString[i][15] = ' ';
            setupString[i][16] = ' ';
            setupString[i][17] = ' '; 
            for(int j = 17; temp >0; j--) 
            {
                setupString[i][j] = (char)temp%10+'0';
                temp = temp/10;
            }
            //Erasing the screen to clear clutter before putting the new string back on
            ncplane_erase(selectionScreen);
        }
    }
    //erase a final time
    ncplane_erase(selectionScreen);
    //set the custom parameters
    setCustomParams(param[0], param[1], param[2]);
}