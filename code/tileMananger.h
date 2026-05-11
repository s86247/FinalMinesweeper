/** @file 
 *@author Tristan Risi, 900367080
 *@date 5/10/2026
*/

#include <stdlib.h>
#include <stdbool.h>
#include <notcurses/notcurses.h>
#include "gameManager.h"

/** 
 * @brief  An enum representing the type of space a tile is
 */
typedef enum typeSpace
{
    BLANK,
    HELPER,
    UNSEEN,
    FLAG
}t_space;

/** 
 * @brief A struct representing any given singular space on a minesweeper board
 */
typedef struct normalTile
{
    struct ncplane* tilePlane; ///< A pointer to the plane each tile takes up
    t_space spaceType; ///< The type of space every tile is
    int minesAdjacent; ///< The number of mines adjacent to any given tile
    int numMines; ///< The number of mines a tile has if its double mine
    bool isMine; ///< A bool thats true if the tile is a mine
    bool isBlack; ///< A bool used for the chess variant that determines if its white or black
}t_tile;

/** 
 * @brief Finds the character representation of a tile based on the game mode and its parameters
 * @param[in] tile The tile that gets checked to find a character representation
 * @param[out] char A character representation of a tile
 * @return The graphical component of a tile
 */
char getTileGraphic(t_tile tile);

/** 
 * @brief Finds the color of a tile based on the game mode and its parameters
 * @param[in] tile The tile that gets checked to find its color
 * @param[out] uint32_t The uint32_t representation of the tiles color
 * @return The color component of a tile
 */
uint32_t getTileColor(t_tile tile);

/** 
 * @brief Lets getTileGraphic know to show mines via updating a common boolean
 * @param[in] lost The boolean value that the common boolean gets updated to
 */
void updateMinesShowing(bool lost);


