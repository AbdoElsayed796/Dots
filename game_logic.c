#include <stdio.h>
#include <stdlib.h>
#include "user_input.h"
#include "grid.h"
#include "ansi_colors.h"

void turns(Grid *gameGrid, gameState *currentGame, int remainingLines)
{
    Player player1, player2;
    player1.symbol = PLAYER1;
    player2.symbol = PLAYER2;
    currentGame->CurrentTurn = enPLAYER_1;
    clock_t start, end;
    static int time_taken_s = 0;
    static int time_taken_m = 0;

    printGrid((*gameGrid), currentGame);
    while (remainingLines >= 0)
    {
        start = clock();
        switch (currentGame->CurrentTurn)
        {
        case enPLAYER_1:
            updateGridWithUserInput(gameGrid, player1, currentGame, getUserInput(gameGrid->size));
            printGrid((*gameGrid), currentGame);
            break;
        case enPLAYER_2:
            updateGridWithUserInput(gameGrid, player2, currentGame, getUserInput(gameGrid->size));
            printGrid((*gameGrid), currentGame);
            break;
        }
        end = clock();
        time_taken_s += (int)(end - start) / CLOCKS_PER_SEC;
        time_taken_m+=time_taken_s/60;
        time_taken_s%=60;
        printf(CYN"Time : %02dm:%02ds\n" RESET,time_taken_m,time_taken_s);
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
bool checkAndMarkClosedBox(int i, int j, Grid *gameGrid, char playerSymbol, gameState *currentGame)
{
    if (countBoxSides(i, j, gameGrid) == 4)
    {
        gameGrid->grid[i][j] = playerSymbol;
        markBoxSides(i, j, gameGrid, playerSymbol);
        currentGame->remainingBoxes--;
        switch (playerSymbol)
        {
        case PLAYER1:
            currentGame->scoreOfPlayer1++;
            break;
        case PLAYER2:
            currentGame->scoreOfPlayer2++;
            break;
        }
        return true;
    }
    return false;
}
void checkBoxesAroundLine(int i, int j, Grid *gameGrid, char playerSymbol, gameState *currentGame)
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

int main()
{

    unsigned char size = 3;
    Grid gameGrid = createGrid(2 * size - 1);
    initializeGrid(&gameGrid);

    gameState currentGame;
    currentGame.scoreOfPlayer1 = 0;
    currentGame.scoreOfPlayer2 = 0;
    currentGame.remainingLines = (2 * size) * (size - 1);
    currentGame.remainingBoxes = (size-1) * (size-1);
    printGrid(gameGrid, &currentGame);
    turns(&gameGrid, &currentGame, currentGame.remainingLines - 1);
    freeGrid(&gameGrid);

    return 0;
}