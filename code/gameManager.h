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
}t_mode;

typedef enum gameSize
{
    SMALL,
    NORMAL,
    LARGE,
    GIANT
}t_size;

void setGameState(t_state state);

t_state getGameState();

void setGameMode(t_mode mode);

t_mode getGameMode();

void setGameSize(t_size size);

int getGameSize(bool isRow);

int getTotalMineCount();