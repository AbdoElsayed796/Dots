#include <stdio.h>
#include "user_input.h"
#include "grid.h"

int main()
{
    unsigned char size = 11;
    Grid gameGrid = createGrid(size);
    initializeGrid(&gameGrid);
    Player player;
    player.symbol = PLAYER1;
    printGrid(gameGrid);
    updateGridWithUserInput(&gameGrid, player, getUserInput(gameGrid.size));
    freeGrid(&gameGrid);

    return 0;
}