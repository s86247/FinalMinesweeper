Thank you for playing, this read me has been split up into 3 main sections:

1.) HOW TO PLAY
Firstly the game is run off standard make controls so the bash command to run the game in your terminal is: "make all && ./minesweeper"
The basic controls are given in the main menu but generally it's 'C' or 'Z' to clear a tile or confirm, 'F' or 'X' to flag a tile, arrow keys or WASD to move, R to restart and ESC to quit.
The goal of the game is to flag all of the remaining tiles correctly without clearing any mines. This goal stays the same throughout all modes.

2.)GAME SIZES AND GAME MODES
There are three preprogrammed sizes, small with a 9x9 board and ten mines, normal with a 16x16 board and 40 mines, and large with a 30x16 board and 99 mines.
You can also make a custom size with the smallest being 4x4 with 4 mines and the largest being 99x99 with 999 mines.
Beyond basic minesweeper there are four additonal modes

CHESS:
The board becomes black and white where number tiles count mines on opposite color tiles as one mine and same color tiles as two mines.
So if a number tile was on a black tile and had an adjacent mine on a white and black tile it would show a three count, where the black counts as two and the white counts as one.

LIAR:
Every number tile on the board is off by one with a minimum count of 0

DOUBLE BOMB:
Every time a mine is placed a 20% chance is rolled for another mine to be placed on that same tile, this happens repeatedly until the 20% chance fails.
This doesn't affect the number of flags needed to be placed only the way adjacent tiles count mines.
So a number may show three when only one tile is a mine as there are three mines on that tile.
The total number of mines is show in the overall mine count and the mines left to flag are shown in the num mines count.

TIME TRIAL:
This is the same as standard except depending on the board size you're racing against times to beat.
After you beat the developer times your new time will be set as the time to beat and you can reset to try and get a new record.
The inital times to beat are as follows:
EASY: 31s
MEDIUM: 192s
LARGE: 689s


3.)NOTES
This section is just a couple of notes on limitations within the project and why they're there.
Firstly this is keyboard based. I tried to implement mouse controls via the GPM library, but, as far as I know, running Linux through WSL means that Linux can't get acsess to your mouse drivers and in turn GPM doesnt work. I'm unsure if there are any work arounds but I stopped and opted for keyboard controls shortly after learning about the driver issue.
For chess I got rid of the unique colors for each number and chose to instead have everything be black and white. I did this for two main reasons. Firstly I felt it made seeing what was going on easier. And secondly making the backgrounds of the cells change color left either ugly gaps or made the grid pattern less clear.
This leads into another limitation which is all of my graphics are character based and not sprite based. There's no great reason for that other than time constraints but it has an impact on things like chess as mentioned previously.
Finally I'm unsure of how truly random my random based functions are. I tried to mitigatie it and I'm happy with the results but when playing "Liar" for example you can see that several tiles will be minus one in a row when first gernerated.

