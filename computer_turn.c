#include <stdlib.h>
#include "game_definitions.h"
#include "grid.h"
#include "game_logic.h"
#include <unistd.h>

char chooseBestSide(int i, int j, Grid *gameGrid, SmallNumber *sidesCount, char currentChoice)
{
    char bestChoice = currentChoice;
    SmallNumber currentBoxSidesNum;
    if (i % 2 == 0)
    {
        if (i == 0)
        {
            currentBoxSidesNum = countBoxSides(i + 1, j, gameGrid);
            if (*sidesCount >= currentBoxSidesNum)
            {
                *sidesCount = currentBoxSidesNum;
                bestChoice = gameGrid->grid[i][j];
            }
        }
        else if (i == gameGrid->size - 1)
        {
            currentBoxSidesNum = countBoxSides(i - 1, j, gameGrid);
            if (*sidesCount >= currentBoxSidesNum)
            {
                *sidesCount = currentBoxSidesNum;
                bestChoice = gameGrid->grid[i][j];
            }
        }
        else
        {
            currentBoxSidesNum = countBoxSides(i + 1, j, gameGrid) + countBoxSides(i - 1, j, gameGrid);
            if (*sidesCount >= currentBoxSidesNum)
            {
                *sidesCount = currentBoxSidesNum;
                bestChoice = gameGrid->grid[i][j];
            }
        }
    }
    else
    {
        if (j == 0)
        {
            currentBoxSidesNum = countBoxSides(i, j + 1, gameGrid);
            if (*sidesCount >= currentBoxSidesNum)
            {
                *sidesCount = currentBoxSidesNum;
                bestChoice = gameGrid->grid[i][j];
            }
        }
        else if (j == gameGrid->size - 1)
        {
            currentBoxSidesNum = countBoxSides(i, j - 1, gameGrid);
            if (*sidesCount >= countBoxSides(i, j - 1, gameGrid))
            {
                *sidesCount = currentBoxSidesNum;
                bestChoice = gameGrid->grid[i][j];
            }
        }
        else
        {
            currentBoxSidesNum = countBoxSides(i, j + 1, gameGrid) + countBoxSides(i, j - 1, gameGrid);
            if (*sidesCount >= currentBoxSidesNum)
            {
                *sidesCount = currentBoxSidesNum;
                bestChoice = gameGrid->grid[i][j];
            }
        }
    }
    return bestChoice;
}

char chooseOpenedSide(SmallNumber i, SmallNumber j, Grid *gameGrid, bool completeBox)
{
    char chosenSide;
    SmallNumber row, column, sidesCountInBox = 4;
    SmallNumber directionalArr[2][4] = {
        {0, 0, 1, -1},
        {1, -1, 0, 0}};

    for (int k = 0; k < 4; k++)
    {
        row = i + directionalArr[0][k];
        column = j + directionalArr[1][k];
        if (completeBox)
        {
            if ((gameGrid->grid[row][column] != PLAYER1) && (gameGrid->grid[row][column] != PLAYER2))
            {
                return gameGrid->grid[row][column];
            }
        }
        else
        {
            if ((gameGrid->grid[row][column] != PLAYER1) && (gameGrid->grid[row][column] != PLAYER2))
            {
                chosenSide = chooseBestSide(row, column, gameGrid, &sidesCountInBox, chosenSide);
            }
        }
    }
    return chosenSide;
}

void computerTurn(Grid *gameGrid, char playerSymbol, GameState *currentGame, MovesHistory *movesHistory)
{
    for (int i = 1; i < gameGrid->size; i += 2)
        for (int j = 1; j < gameGrid->size; j += 2)
            if (countBoxSides(i, j, gameGrid) == 3)
            {
                updateGridWithUserInput(gameGrid, playerSymbol, currentGame, chooseOpenedSide(i, j, gameGrid, true), movesHistory, false);
                return;
            }
    for (int k = 0; k < 3; k++)
        for (int i = 1; i < gameGrid->size; i += 2)
            for (int j = 1; j < gameGrid->size; j += 2)
                if (countBoxSides(i, j, gameGrid) == k)
                {
                    updateGridWithUserInput(gameGrid, playerSymbol, currentGame, chooseOpenedSide(i, j, gameGrid, false), movesHistory, false);
                    return;
                }
}