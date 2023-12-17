#include <stdio.h>
#include "grid.h"

unsigned char getUserInput()
{
    unsigned char userInput;

}
int main()
{
    unsigned char size = 7;
    Grid gameGrid = createGrid(size);

    initializeGrid(&gameGrid);
    // gameGrid.grid[0][1] = PLAYER1;
    // gameGrid.grid[2][1] = PLAYER2;
    // gameGrid.grid[1][0] = PLAYER2;
    // gameGrid.grid[0][3] = PLAYER2;

    // gameGrid.grid[1][4] = PLAYER2;
    // gameGrid.grid[3][2] = PLAYER1;
    // gameGrid.grid[1][2] = PLAYER2;
    // gameGrid.grid[1][1] = PLAYER2;
    // gameGrid.grid[1][3] = PLAYER2;
    // gameGrid.grid[3][1] = PLAYER2;
    // gameGrid.grid[1][5] = PLAYER1;
    // gameGrid.grid[1][6] = PLAYER2;

    printGrid(gameGrid);

    freeGrid(&gameGrid);

    return 0;
}