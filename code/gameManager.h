/** @file 
 *@author Tristan Risi, 900367080
 *@date 5/10/2026
*/


#include <stdlib.h>
#include <stdbool.h>

/**@brief An enum that keeps track if the player lost, won or if they're still playing*/
typedef enum gameState
{
    WON,
    LOST,
    PLAYING
}t_state;

/**@brief An enum that keeps track of the players chosen gamemode with: Standard, Chess, Liar, Double Mine, and Time Trial*/
typedef enum gameMode
{
    STANDARD,
    CHESS,
    LIAR,
    DOUBLEMINE,
    TIME
}t_mode;

/**@brief An enum that keeps track if the player lost, won or if they're still playing*/
typedef enum gameSize
{
    SMALL,
    NORMAL,
    LARGE,
    CUSTOM
}t_size;

/** 
* @brief Sets the universal game state to the given state
* @param[in] state An enum of the desired game state
*/
void setGameState(t_state state);


/** 
 * @brief  Gets the universal game state
 * @param[out] t_state An enum representation of the universal game state
 * @return the universal game state
 */
t_state getGameState();

/** 
* @brief Sets the universal game mode to the given mode
* @param[in] mode An enum of the desired game mode
*/
void setGameMode(t_mode mode);

/** 
 * @brief  Gets the universal game mode
 * @param[out] t_mode An enum representation of the universal game mode
 * @return the universal game mode
 */
t_mode getGameMode();


/** 
* @brief Sets the universal game size to the given size
* @param[in] mode An enum of the desired game size
*/
void setGameSize(t_size size);


/** 
 * @brief  Gets either the number of rows or number of columns with respect to the universal game size
 * @param[in] isRow A bool that determines if the function should return the number of rows or columns
 * @param[out] int An integer representing either the row count or the column count
 * @return one aspect of the total board size
 */
int getGameSize(bool isRow);

/** 
 * @brief  Gets the universal game size
 * @param[out] t_size An enum representation of the universal game size
 * @return the universal game size
 */
t_size getUniversalGameSize();


/** 
 * @brief  Gets the total number of expected mines in relation to the universal game size
 * @param[out] int An int of the total number of mines the board should have
 * @return the mines on the board
 */
int getTotalMineCount();

/** 
 * @brief  Sets the rows, columns, and mines entered by a user as constants to be acsessed through the CUSTOM size enum
 * @param[in] row The number of rows the user wanted for the custom board
 * @param[in] col The number of columns the user wanted for the custom board
 * @param[in] mines The number of mines the user wanted for the custom board
 */
void setCustomParams(int row, int col, int mines);