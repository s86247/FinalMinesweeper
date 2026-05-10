#include <stdlib.h>
#include <stdbool.h>

typedef enum gameState
{
    MENU,
    WON,
    LOST,
    PLAYING
}t_state;

typedef enum gameMode
{
    STANDARD,
    CHESS,
    LIAR,
    DOUBLEMINE,
    TIME
}t_mode;

typedef enum gameSize
{
    SMALL,
    NORMAL,
    LARGE,
    CUSTOM
}t_size;

void setGameState(t_state state);

t_state getGameState();

void setGameMode(t_mode mode);

t_mode getGameMode();

void setGameSize(t_size size);

int getGameSize(bool isRow);

t_size getUniversalGameSize();

int getTotalMineCount();

void setCustomParams(int row, int col, int mines);