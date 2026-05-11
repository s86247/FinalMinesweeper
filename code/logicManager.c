/** @file 
 *@author Tristan Risi, 900367080
 *@date 5/10/2026
*/

#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <notcurses/notcurses.h>

#include "logicManager.h"

//The NCplane for the stats screen
struct ncplane *statsPlane = NULL;
//A string used to keep the mine count 
char str[14] ={"Num Mines:000"};
//A running count of how many mines the player has yet to clear
int numMinesLeft;
//Only false if the user hasnt cleared anything
bool firstSpaceCleared;
//A bool thats true when a win or loss is because of timeTrial
bool isTimeRelated = false;

struct ncplane_options statsOptions = {
    .rows = 4,
    .cols = 18,
};

void initializeLogic()
{
    //Makes and sets a seed according to both the time and identity of the function call
    srand(time(NULL) ^ getpid());
    //Sets default variables
    numMinesLeft = getTotalMineCount();
    firstSpaceCleared = false;
    //Creates the NCplane for the stats screen
    statsPlane = ncplane_create(getStandardPlane(),  &statsOptions);
    ncplane_move_yx(statsPlane, 2, getGameSize(false)*2+6);
    str[11]= (char)(numMinesLeft/10)+'0';
    str[12]= (char)(numMinesLeft%10)+'0';
    ncplane_putstr_yx(statsPlane, 0, 0, str);
}

void affectTile(t_input input)
{
    if(input == CLEARED && !firstSpaceCleared)
    {
        firstSpaceCleared = true;
        generateMines();
        char totalMinesString[17] = "Overall Mines:000";
        int temp;
        temp = getRealMines();
        //Updates the stats screen to have the overall mine count 
        for(int j = 16; temp >0; j--) 
        {
            totalMinesString[j] = (char)((temp % 10) + '0');
            temp = temp/10;
        }
        ncplane_putstr_yx(statsPlane, 1, 0, totalMinesString);
    }

    if (getTileRelative(0,0).spaceType == BLANK || getTileRelative(0,0).spaceType == HELPER){return;}
    else if(input == CLEARED && numMinesLeft >0)
    {
        if(getTileRelative(0,0).isMine){setGameState(LOST);}
        else if(getTileRelative(0,0).spaceType == UNSEEN){reveal(0,0);}
    }
    else if(input == FLAGGED)
    {
        //if Flagged unflag minecount back up
        if( getTileRelative(0,0).spaceType == FLAG)
        {
            changeTileSpaceTypeRelative(0,0, UNSEEN);
            numMinesLeft ++;
        }
        //if not flagged flag mine count down
        else if(numMinesLeft >0)
        {
            changeTileSpaceTypeRelative(0,0, FLAG);
            numMinesLeft --;
        }
    }
    else {return;}

    //if the user has placed all their flags
    if(numMinesLeft <= 0)
    {
        //check if all the mines have been flagged
        if(getTotalMineCount() == takeMineCount()) 
        {
            //if so they've won
            setGameState(WON);
            //if they've won and they havent went past the time they set a new record
            if(getGameMode() == TIME && isTimeRelated == false){setIsTimeRelated(true);}
        }
    }

    //Prints out the running mine count with num mines 
    int temp = numMinesLeft;
    str[12] = ' ';
    str[11] = ' ';
    str[10] = ' ';
    for(int j = 12; temp >0; j--) 
    {
        str[j] = (char)((temp % 10) + '0');
        temp = temp/10;
    }
    ncplane_putstr_yx(statsPlane, 0, 0, str);
}


void reveal(int rowOffset, int colOffset)
{
    int numMinesAdj = 0;
    //temp variable that allows the reveal function to accept 0 as a valid number of adjacent mines
    bool liarCanContinue = false;
    for(int i=-1; i<2; i++)
    {
        for(int j=-1; j<2; j++)
        {
            if(!(i == 0 && j == 0)) 
            {
                //get the tile at the offset in a 3x3 grid
                t_tile emtpyTileChecker = getTileRelative(rowOffset + i,colOffset+j);
                //make sure its not a null tile
                if(emtpyTileChecker.minesAdjacent == -1){continue;}
                //if its chess and same color mines adjacent is 2 and if diffrent color 1
                else if(emtpyTileChecker.isMine && getGameMode() == CHESS)
                {
                    if(emtpyTileChecker.isBlack == getTileRelative(rowOffset,colOffset).isBlack){numMinesAdj+=2;}
                    else{numMinesAdj++;}
                }
                //if its anything else but double mine then its just 1 more mine
                else if(emtpyTileChecker.isMine && getGameMode() != DOUBLEMINE){numMinesAdj++;}
                //if its double mine the count is upped by the number of mines on a tile
                else{numMinesAdj+=emtpyTileChecker.numMines;}
            }
        }
    }
    //if the game mode is liar then the count is set off by one and its allowed to pass as a helper
    if(getGameMode() == LIAR && numMinesAdj>0)
    {
        if(rand() % 2 == 0){numMinesAdj--;}
        else{numMinesAdj++;}
        liarCanContinue = true;
    }
    //If the tile has adjacent mines its set as a helper and the recurrsion ends
    if(numMinesAdj>0|| liarCanContinue == true)
    {
        setMinesAdjacentRelative(rowOffset,colOffset,numMinesAdj);
        changeTileSpaceTypeRelative(rowOffset,colOffset,HELPER);
    }
    //If not its set as blank and the loop recursivley goes to the next 8 adjacent tiles
    else
    {
        changeTileSpaceTypeRelative(rowOffset,colOffset,BLANK);
        for(int i=-1; i<2; i++)
        {
            for(int j=-1; j<2; j++)
            {
                if(!(i==rowOffset && j == colOffset))
                {
                    t_tile emtpyTileChecker = getTileRelative(rowOffset + i,colOffset+j);
                    if(emtpyTileChecker.minesAdjacent == -1){continue;}
                    else if(emtpyTileChecker.spaceType!=BLANK&&!emtpyTileChecker.isMine){reveal(rowOffset + i,colOffset+j);}
                }
            }
        }
    }
}


void updateStats(time_t start, time_t end)
{
    if(getGameState() == WON && isTimeRelated == true){ncplane_putstr_yx(statsPlane, 3, 0, "RECORD TIME :0");}
    else if(getGameState() == WON){ncplane_putstr_yx(statsPlane, 3, 0, "YOU WON :)");}
    else if(getGameState() == LOST && isTimeRelated == true){ncplane_putstr_yx(statsPlane, 3, 0, "TOO SLOW :(");}
    else if(getGameState() == LOST){ncplane_putstr_yx(statsPlane, 3, 0, "YOU LOST :(");}
    else 
    {
        //Prints the minutes and seconds elapsed in accordance to the totalseconds
        int totalSeconds = (int)difftime(end, start);

        int minutes = totalSeconds / 60;
        int seconds = totalSeconds % 60;

        char timeStr[15]  = "Time: 00:00";

        timeStr[6]= (char)(minutes/10)+'0';
        timeStr[7]= (char)(minutes%10)+'0';

        timeStr[9]= (char)(seconds/10)+'0';
        timeStr[10]= (char)(seconds%10)+'0';

        ncplane_putstr_yx(statsPlane, 2, 0, timeStr);
    }
}

void resetScreen()
{
    ncplane_erase(getStandardPlane());
    ncplane_erase(statsPlane);
}

void setIsTimeRelated(bool is)
{
    isTimeRelated = is;
}