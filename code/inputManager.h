/** @file 
 *@author Tristan Risi, 900367080
 *@date 5/10/2026
*/

#include <stdlib.h>
#include <stdbool.h>
#include <notcurses/notcurses.h>


/** 
 * @brief An enum representing potential choices a player make
*/
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

/** 
 * @brief  Initalizes the base NotCurses refrence for itself and other programs
*/
void initializeInput();

/** 
 * @brief  Waits for user input and then assigns the given key press a corresponding t_input
 * @param[out] t_input An enum representation of the user's input
 * @return the action a user took with their input
 */
t_input get_input();


/** 
 * @brief  Returns the universal NotCurses refrence
 * @param[out] notcurses* The universal NotCurses refrence for the program
 * @return A pointer to the NotCurses refrence
 */
struct notcurses* getNotCursesRefrence();