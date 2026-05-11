/** @file 
 *@author Tristan Risi, 900367080
 *@date 5/10/2026
*/

#include <stdlib.h>
#include <stdbool.h>
#include <notcurses/notcurses.h>

#include "tileMananger.h"
#include "inputManager.h"

/** 
 * @brief Sets the standard NCplane for both the board and menu
 */
void setStandardPlane();

/** 
 * @brief  Returns the standard NCplane refrence
 * @param[out] ncplane* The standard NCplane refrence for the program
 * @return A pointer to the NCplane refrence
 */
struct ncplane* getStandardPlane();

/** 
 * @brief Allocates a double array in memory of t_tile according to the games size and sets the tile values to appropriate defaults 
 */
void initializeBoard();

/** 
 * @brief Frees the memory stored in gameBoard
 */
void freeBoard();

/** 
 * @brief  Updates the standard plane with the current character representation and color of each tile
 */
void printBoard();

/** 
 * @brief  Moves the cursor, up, down, left, or right according to the t_input passed in
 * @param[in] t_input The movement action the player took
 */
void moveCursor(t_input movement);

/** 
 * @brief  Changes the color of the initally selected tile back to its original color then highlights and stores the new selected tile
 * @param[in] t_tile The tile the player selected
 */
void updateSelectedTile(t_tile tile);

/** 
 * @brief  Goes through every tile on the board with a 10% to make any valid tile a mine. Repeats until mines placed equals getTotalMineCount()
 * @param[out] int The total number of mines put on the board
 * @return The number of mines really generated to gaurentee sucsessful placement.
 */
int generateMines();

/** 
 * @brief Calculates the distance between two mines on the board
 * @param[in] row1 The row index of tile 1
 * @param[in] col1 The col index of tile 1
 * @param[in] row2 The row index of tile 2
 * @param[in] col2 The col index of tile 2
 * @param[out] int The integer representation of tile distance
 * @return The total distance between two tiles 
 */
int getTileDistance(int row1, int col1, int row2, int col2);

/** 
 * @brief Gets the tile realative to the selected tile
 * @param[in] row The row offset from the selceted tile
 * @param[in] col The col offset from the selceted tile
 * @param[out] t_tile The t_tile at the offset from the selected tile
 * @return The tile at the offset
 */
t_tile getTileRelative(int row, int col);

/** 
 * @brief Changes the space type of the tile realative to the selected tile
 * @param[in] row The row offset from the selceted tile
 * @param[in] col The col offset from the selceted tile
 * @param[in] space The new space type for the tile at the offset
 */
void changeTileSpaceTypeRelative(int row, int col, t_space space);

/** 
 * @brief Sets the number of mines adjacent for the tile realative to the selected tile
 * @param[in] row The row offset from the selceted tile
 * @param[in] col The col offset from the selceted tile
 * @param[in] mines The mines adjacent of the tile at the offset
 */
void setMinesAdjacentRelative(int row, int col, int mines);

/** 
 * @brief Checks if any given coordinates are in the bounds of the game board and returns true if it is
 * @param[in] row The row of the index being checked
 * @param[in] col The col of the index being checked
 * @param[out] bool A boolean representing if its in bounds
 * @return if it is in bounds or not
 */
bool isInBounds(int row, int col);

/** 
 * @brief Takes the count of mines correctly flagged by the player
 * @param[out] int An int representing the number of mines the player correctly flagged
 * @return The number of mines the player correctly flagged
 */
int takeMineCount();

/** 
 * @brief returns the real mine count for double mine
 * @param[out] int An int representing the number of mines placed in total
 * @return The total number of mines placed.
 */
int getRealMines();