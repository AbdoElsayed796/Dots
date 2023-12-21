#include <stdio.h>
#include <stdlib.h>
#include "user_input.h"

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
void checkAndMarkClosedBox(int i, int j, Grid *gameGrid, char playerSymbol)
{
    if (countBoxSides(i, j, gameGrid) == 4)
    {
        gameGrid->grid[i][j] = playerSymbol;
        markBoxSides(i, j, gameGrid, playerSymbol);
    }
}
void checkBoxesAroundLine(int i, int j, Grid *gameGrid, char playerSymbol)
{
    if (i % 2 == 0)
    {
        if (i == 0)
            checkAndMarkClosedBox(i + 1, j, gameGrid, playerSymbol);
        else if (i == gameGrid->size - 1)
            checkAndMarkClosedBox(i - 1, j, gameGrid, playerSymbol);
        else
        {
            checkAndMarkClosedBox(i + 1, j, gameGrid, playerSymbol);
            checkAndMarkClosedBox(i - 1, j, gameGrid, playerSymbol);
        }
    }
    else
    {
        if (j == 0)
            checkAndMarkClosedBox(i, j + 1, gameGrid, playerSymbol);
        else if (i == gameGrid->size - 1)
            checkAndMarkClosedBox(i, j - 1, gameGrid, playerSymbol);
        else
        {
            checkAndMarkClosedBox(i, j - 1, gameGrid, playerSymbol);
            checkAndMarkClosedBox(i, j + 1, gameGrid, playerSymbol);
        }
    }
}

int main()
{
    unsigned char size = 5;
    Grid gameGrid = createGrid(size);
    initializeGrid(&gameGrid);

    Player player1, player2;
    player1.symbol = PLAYER1;
    player2.symbol = PLAYER2;
    printGrid(gameGrid);

    for (int i = 1; i <= 9; i++)
    {
        updateGridWithUserInput(&gameGrid, player2, getUserInput(gameGrid.size));
        printGrid(gameGrid);
        updateGridWithUserInput(&gameGrid, player1, getUserInput(gameGrid.size));
        printGrid(gameGrid);
    }
    // SmallNumber v = countBoxSides(1, 1, &gameGrid);
    // printf("%d", v);
    freeGrid(&gameGrid);

    return 0;
}