#include <stdio.h>
#include "user_input.h"

SmallNumber CheckClosedBoxes(SmallNumber i,SmallNumber j, Grid *gameGrid)
{   int row,column;
    int Direction[2][4] = {
        {0, 0, 1, 0 - 1},
        {1, -1, 0, 0}};
    SmallNumber NumberOfClosedSides = 0;
    for (int k = 0; k < 4; k++)
    {row=i+Direction[0][k];
     column=j+Direction[1][k];

        if (gameGrid->grid[row][column]==PLAYER1 || gameGrid->grid[row][column]==PLAYER2)
        {
            NumberOfClosedSides++;
        }
    }
    return NumberOfClosedSides;
}

int main()
{
    unsigned char size = 11;
    Grid gameGrid = createGrid(size);
    initializeGrid(&gameGrid);
     Player player;
     player.symbol = PLAYER1;
     printGrid(gameGrid);
     updateGridWithUserInput(&gameGrid, player, getUserInput(gameGrid.size));
     gameGrid.grid[0][1]=gameGrid.grid[1][0]=gameGrid.grid[1][2]=gameGrid.grid[2][1]=PLAYER1;
     printGrid(gameGrid);
    SmallNumber v=CheckClosedBoxes(1,1,&gameGrid);
    printf("%d",v);
    freeGrid(&gameGrid);

    return 0;
}