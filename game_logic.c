#include <stdlib.h>
#include "user_input.h"
#include "grid.h"
#include "ansi_colors.h"
#include "undo_redo.h"


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
bool checkAndMarkClosedBox(int i, int j, Grid *gameGrid, char playerSymbol, GameState *currentGame)
{
    if (countBoxSides(i, j, gameGrid) == 4)
    {
        gameGrid->grid[i][j] = playerSymbol;
        markBoxSides(i, j, gameGrid, playerSymbol);
        currentGame->remainingBoxes--;
        switch (playerSymbol)
        {
        case PLAYER1:
            currentGame->player1Score++;
            break;
        case PLAYER2:
            currentGame->player2Score++;
            break;
        }
        return true;
    }
    return false;
}
void switchTurns(bool closedABox, GameState *currentGame)
{
    if (!closedABox)
    {
        switch (currentGame->CurrentTurn)
        {
        case enPLAYER_1:
            currentGame->CurrentTurn = enPLAYER_2;
            break;
        case enPLAYER_2:
            currentGame->CurrentTurn = enPLAYER_1;
            break;
        }
    }
}
void checkBoxesAroundLine(int i, int j, Grid *gameGrid, char playerSymbol, GameState *currentGame)
{
    bool closedABox = false;
    if (i % 2 == 0)
    {
        if (i == 0)
            closedABox |= checkAndMarkClosedBox(i + 1, j, gameGrid, playerSymbol, currentGame);
        else if (i == gameGrid->size - 1)
            closedABox |= checkAndMarkClosedBox(i - 1, j, gameGrid, playerSymbol, currentGame);
        else
        {
            closedABox |= checkAndMarkClosedBox(i + 1, j, gameGrid, playerSymbol, currentGame);
            closedABox |= checkAndMarkClosedBox(i - 1, j, gameGrid, playerSymbol, currentGame);
        }
    }
    else
    {
        if (j == 0)
            closedABox |= checkAndMarkClosedBox(i, j + 1, gameGrid, playerSymbol, currentGame);
        else if (i == gameGrid->size - 1)
            closedABox |= checkAndMarkClosedBox(i, j - 1, gameGrid, playerSymbol, currentGame);
        else
        {
            closedABox |= checkAndMarkClosedBox(i, j - 1, gameGrid, playerSymbol, currentGame);
            closedABox |= checkAndMarkClosedBox(i, j + 1, gameGrid, playerSymbol, currentGame);
        }
    }
    switchTurns(closedABox, currentGame);
}