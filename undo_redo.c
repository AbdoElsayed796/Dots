#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "game_definitions.h"
#include "game_logic.h"

void undoGameState(MovesHistory *movesHistory, GameState *currentGame, int openedBoxesCount, char symbol)
{
    (movesHistory->numMovesPlayed)++;
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

void openBox(SmallNumber i, SmallNumber j, Grid *gameGrid, SmallNumber *openedBoxesCount)
{
    gameGrid->grid[i][j] = ' ';
    if (countBoxSides(i, j, gameGrid) == 3)
        (*openedBoxesCount)++;
}

SmallNumber updateBoxStatusAfterUndo(Grid *gameGrid, MovesHistory *movesHistory, GameState *currentGame)
{
    SmallNumber openedBoxesCount = 0;
    char symbol = movesHistory->moves[movesHistory->currentMove].playerSymbol;
    SmallNumber i = movesHistory->moves[movesHistory->currentMove].i;
    SmallNumber j = movesHistory->moves[movesHistory->currentMove].j;

    if (i % 2 == 0)
        if (i == 0)
            openBox(i + 1, j, gameGrid, &openedBoxesCount);
        else if (i == gameGrid->size - 1)
            openBox(i - 1, j, gameGrid, &openedBoxesCount);
        else
        {
            openBox(i - 1, j, gameGrid, &openedBoxesCount);
            openBox(i + 1, j, gameGrid, &openedBoxesCount);
        }
    else if (j % 2 == 0)
        if (j == 0)
            openBox(i, j + 1, gameGrid, &openedBoxesCount);
        else if (j == gameGrid->size - 1)
            openBox(i, j - 1, gameGrid, &openedBoxesCount);
        else
        {
            openBox(i, j + 1, gameGrid, &openedBoxesCount);
            openBox(i, j - 1, gameGrid, &openedBoxesCount);
        }
    return openedBoxesCount;
}

void undo(Grid *gameGrid, MovesHistory *movesHistory, GameState *currentGame)
{
    char symbol = movesHistory->moves[movesHistory->currentMove].playerSymbol;
    SmallNumber i = movesHistory->moves[movesHistory->currentMove].i;
    SmallNumber j = movesHistory->moves[movesHistory->currentMove].j;

    gameGrid->grid[i][j] = movesHistory->moves[movesHistory->currentMove].oldValue;
    undoGameState(movesHistory, currentGame, updateBoxStatusAfterUndo(gameGrid, movesHistory, currentGame), symbol);
}

void redo(Grid *gameGrid, MovesHistory *movesHistory, GameState *currentGame)
{
    (movesHistory->currentMove)++;
    char playerSymbol = movesHistory->moves[movesHistory->currentMove].playerSymbol;
    char characterToChoose = movesHistory->moves[movesHistory->currentMove].oldValue;
    updateGridWithUserInput(gameGrid, playerSymbol, currentGame, characterToChoose, movesHistory);
}

void addMoveToHistory(SmallNumber i, SmallNumber j, char oldValue, char playerSymbol, MovesHistory *movesHistory)
{
    movesHistory->moves[movesHistory->currentMove + 1].i = i;
    movesHistory->moves[movesHistory->currentMove + 1].j = j;
    movesHistory->moves[movesHistory->currentMove + 1].oldValue = oldValue;
    movesHistory->moves[movesHistory->currentMove + 1].playerSymbol = playerSymbol;
   (movesHistory->currentMove)++;
    (movesHistory->numMovesPlayed)++;
}
