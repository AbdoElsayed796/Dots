#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "user_input.h"


void turns(Grid *gameGrid , gameCounts *currentGame, int remainingLines)
{  
    Player player1, player2;
    player1.symbol = PLAYER1;
    player2.symbol = PLAYER2;
  while (remainingLines>0)
  {
      updateGridWithUserInput(gameGrid, player2,currentGame, getUserInput(gameGrid->size));
        printGrid(*gameGrid,currentGame);
        updateGridWithUserInput(gameGrid, player1,currentGame, getUserInput(gameGrid->size));
        printGrid(*gameGrid,currentGame);
        remainingLines--;
  }  
}

SmallNumber countBoxSides(int i, int j, Grid *gameGrid) //* returns number of closed sides around a box
{
    SmallNumber row, column;
    SmallNumber directionalArr[2][4] = {
        {0, 0, 1, -1},
        {1, -1, 0, 0}};
    SmallNumber numberOfClosedSides = 0;
    for (int k = 0; k < 4; k++)
    {
        row = i + directionalArr[0][k];
        column = j + directionalArr[1][k];

        if (gameGrid->grid[row][column] == PLAYER1 || gameGrid->grid[row][column] == PLAYER2)
            numberOfClosedSides++;
    }
    return numberOfClosedSides;
}
void markBoxSides(int i, int j, Grid *gameGrid, char playerSymbol)
{
    SmallNumber row, column;
    SmallNumber directionalArr[2][4] = {
        {0, 0, 1, 0 - 1},
        {1, -1, 0, 0}};

    for (int k = 0; k < 4; k++)
    {
        row = i + directionalArr[0][k];
        column = j + directionalArr[1][k];
        gameGrid->grid[row][column] = playerSymbol;
    }
}
void checkAndMarkClosedBox(int i, int j, Grid *gameGrid, char playerSymbol,gameCounts *currentGame)
{
    if (countBoxSides(i, j, gameGrid) == 4)
    {
        gameGrid->grid[i][j] = playerSymbol;
        markBoxSides(i, j, gameGrid, playerSymbol);
         currentGame->remainingBoxes--;
         switch(playerSymbol)
           {
             case 1:
             currentGame->scoreOfPlayer1++;
             break;
             case 2:
             currentGame->scoreOfPlayer2++;
             break;
           }
    }
   
}
void checkBoxesAroundLine(int i, int j, Grid *gameGrid, char playerSymbol,gameCounts *currentGame)
{
    if (i % 2 == 0)
    {
        if (i == 0)
            checkAndMarkClosedBox(i + 1, j, gameGrid, playerSymbol,currentGame);
        else if (i == gameGrid->size - 1)
            checkAndMarkClosedBox(i - 1, j, gameGrid, playerSymbol,currentGame);
        else
        {
            checkAndMarkClosedBox(i + 1, j, gameGrid, playerSymbol,currentGame);
            checkAndMarkClosedBox(i - 1, j, gameGrid, playerSymbol,currentGame);
        }
    }
    else
    {
        if (j == 0)
            checkAndMarkClosedBox(i, j + 1, gameGrid, playerSymbol,currentGame);
        else if (i == gameGrid->size - 1)
            checkAndMarkClosedBox(i, j - 1, gameGrid, playerSymbol,currentGame);
        else
        {
            checkAndMarkClosedBox(i, j - 1, gameGrid, playerSymbol,currentGame);
            checkAndMarkClosedBox(i, j + 1, gameGrid, playerSymbol,currentGame);
        }
    }
}

int main()
{   

    unsigned char size = 7;
    Grid gameGrid = createGrid(size);
    initializeGrid(&gameGrid);

    gameCounts currentGame;
    currentGame.scoreOfPlayer1=0;
    currentGame.scoreOfPlayer2=0;
    currentGame.remainingLines=((size-1)/2)*(((size-1)/2)+1)*2;
    currentGame.remainingBoxes=pow(((size-1)/2),2);
    printGrid(gameGrid,&currentGame);
    turns(&gameGrid,&currentGame,currentGame.remainingLines-1);
    freeGrid(&gameGrid);

    return 0;
}