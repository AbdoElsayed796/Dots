#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include "game_definitions.h"
#include "game_logic.h"
#include "ansi_colors.h"

//* Undo Functions
void retriveLinesColors(SmallNumber i, SmallNumber j, Grid *gameGrid, MovesHistory *movesHistory)
{
    SmallNumber row, column;
    SmallNumber directionalArr[2][4] = {
        {0, 0, 1, -1},
        {1, -1, 0, 0}};

    for (int n = movesHistory->currentMove - 1; n >= 0; n--)
    {
        for (int k = 0; k < 4; k++)
        {
            row = i + directionalArr[0][k];
            column = j + directionalArr[1][k];
            if (row == movesHistory->moves[n].i && column == movesHistory->moves[n].j)
            {
                gameGrid->grid[row][column] = movesHistory->moves[n].playerSymbol;
            }
        }
    }
}
void undoGameState(MovesHistory *movesHistory, GameState *currentGame, int openedBoxesCount, char symbol)
{
    (currentGame->remainingLines)++;
    switch (symbol)
    {
    case PLAYER1:
        currentGame->player1Score -= openedBoxesCount;
        break;
    case PLAYER2:
        currentGame->player2Score -= openedBoxesCount;
        break;
    }
    currentGame->remainingBoxes += openedBoxesCount;

    (movesHistory->currentMove)--;
}
void openBox(SmallNumber i, SmallNumber j, Grid *gameGrid, SmallNumber *openedBoxesCount, MovesHistory *movesHistory)
{
    gameGrid->grid[i][j] = ' ';
    if (countBoxSides(i, j, gameGrid) == 3)
    {
        (*openedBoxesCount)++;
        retriveLinesColors(i, j, gameGrid, movesHistory);
    }
}
SmallNumber updateBoxStatusAfterUndo(Grid *gameGrid, MovesHistory *movesHistory, GameState *currentGame)
{
    SmallNumber openedBoxesCount = 0;
    char symbol = movesHistory->moves[movesHistory->currentMove].playerSymbol;
    SmallNumber i = movesHistory->moves[movesHistory->currentMove].i;
    SmallNumber j = movesHistory->moves[movesHistory->currentMove].j;

    if (i % 2 == 0)
        if (i == 0)
            openBox(i + 1, j, gameGrid, &openedBoxesCount, movesHistory);
        else if (i == gameGrid->size - 1)
            openBox(i - 1, j, gameGrid, &openedBoxesCount, movesHistory);
        else
        {
            openBox(i - 1, j, gameGrid, &openedBoxesCount, movesHistory);
            openBox(i + 1, j, gameGrid, &openedBoxesCount, movesHistory);
        }
    else if (j % 2 == 0)
        if (j == 0)
            openBox(i, j + 1, gameGrid, &openedBoxesCount, movesHistory);
        else if (j == gameGrid->size - 1)
            openBox(i, j - 1, gameGrid, &openedBoxesCount, movesHistory);
        else
        {
            openBox(i, j + 1, gameGrid, &openedBoxesCount, movesHistory);
            openBox(i, j - 1, gameGrid, &openedBoxesCount, movesHistory);
        }
    return openedBoxesCount;
}

char undo(Grid *gameGrid, MovesHistory *movesHistory, GameState *currentGame) //! it returns the opposite of the state
{
    if (movesHistory->currentMove == 0)
    {
        printf(BHRED "\n\t\t\t\t\tThere are no moves to undo\n" RESET);
        sleep(1);
        return SUCCESS;
    }
    char symbol = movesHistory->moves[movesHistory->currentMove].playerSymbol;
    SmallNumber i = movesHistory->moves[movesHistory->currentMove].i;
    SmallNumber j = movesHistory->moves[movesHistory->currentMove].j;

    if (movesHistory->moves[movesHistory->currentMove].playerSymbol == PLAYER1)
        currentGame->CurrentTurn = enPLAYER_1;
    else
        currentGame->CurrentTurn = enPLAYER_2;

    gameGrid->grid[i][j] = movesHistory->moves[movesHistory->currentMove].oldValue;
    undoGameState(movesHistory, currentGame, updateBoxStatusAfterUndo(gameGrid, movesHistory, currentGame), symbol);
    return FAILURE;
}
char redo(Grid *gameGrid, MovesHistory *movesHistory, GameState *currentGame) //! it returns the opposite of the state
{
    if (movesHistory->currentMove >= movesHistory->numMovesPlayed)
    {
        printf(BHRED "\n\t\t\t\t\tThere are no moves to redo\n" RESET);
        sleep(1);
        return SUCCESS;
    }

    char playerSymbol = movesHistory->moves[movesHistory->currentMove+1].playerSymbol;
    char characterToChoose = movesHistory->moves[movesHistory->currentMove+1].oldValue;
    updateGridWithUserInput(gameGrid, playerSymbol, currentGame, characterToChoose, movesHistory, true);
    return FAILURE;
}

void addMoveToHistory(SmallNumber i, SmallNumber j, char oldValue, char playerSymbol, MovesHistory *movesHistory, bool isRedo)
{
    movesHistory->moves[movesHistory->currentMove + 1].i = i;
    movesHistory->moves[movesHistory->currentMove + 1].j = j;
    movesHistory->moves[movesHistory->currentMove + 1].oldValue = oldValue;
    movesHistory->moves[movesHistory->currentMove + 1].playerSymbol = playerSymbol;
    (movesHistory->currentMove)++;
    movesHistory->numMovesPlayed = isRedo ? movesHistory->numMovesPlayed : movesHistory->currentMove;
}
