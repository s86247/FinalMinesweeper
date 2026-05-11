/** @file 
 *@author Tristan Risi, 900367080
 *@date 5/10/2026
*/

#include <stdlib.h>
#include <stdbool.h>
#include<time.h>
#include <notcurses/notcurses.h>

#include "boardManager.h"

/** 
 * @brief  Initalized the logicManager with default values and sets up the stats screen
 */
void initializeLogic();

/** 
 * @brief  Affects the selected tile in boardManager according to the users input and preexisting conditions. Also updates mines left on the stats screen
 * @param[in] input The t_input representation of how the user wishes to affect a tile (Clear, flag)
 */
void affectTile(t_input input);

/** 
 * @brief  Reveals the tile at the given offset from the selected tile and if blank recursivley reveals all adjacent blank tile. If not blank it calculates the number of adjacent mines
 * @param[in] rowOffset The row offset from the selected tile
 * @param[in] rowOffset The col offset from the selected tile
 */
void reveal(int rowOffset, int colOffset);

/** 
 * @brief Updates the time elapsed in the game and a message if the user has won or lost
 * @param[in] start The time when the user started the game
 * @param[in] end The last time the user inputted something
 */
void updateStats(time_t start, time_t end);

/** 
 * @brief Resets the screen once the user has finished with the menu
 */
void resetScreen();

/** 
 * @brief Updates a common bool to tell updateStats() if the win or loss was time related in time trial
 */
void setIsTimeRelated(bool is);