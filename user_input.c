#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include "ansi_colors.h"
#include "game_logic.h"
#include "undo_redo.h"
#include "game_definitions.h"
#include "save_load.h"

void pause()
{
    printf("\nPress any key to continue ...\n");
    getche();
    getche();
}
void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

//* User Input
bool isValidGridInput(char userInput, char gridSize) //* validate user input based on grid size
{
    bool inputInGrid;

    if (gridSize == 9 || gridSize == 11)
    {
        inputInGrid = (userInput >= '0' && userInput <= '9') ||
                      (userInput >= 'A' && userInput <= 'Z') ||
                      (userInput >= 'a' && userInput <= (gridSize * 10 + 10));
    }
    else
        switch (gridSize)
        {
        case 5:
            inputInGrid = (userInput >= '0' && userInput <= '9') || (userInput >= 'A' && userInput <= 'B');
            break;
        case 7:
            inputInGrid = (userInput >= '0' && userInput <= '9') || (userInput >= 'A' && userInput <= 'N');
            break;
        default:
            printf("Invalid grid size");
            exit(1);
        }
    return inputInGrid;
}
UserAction getUserAction(char *userInput)
{
    if (strncmp(userInput, "undo", 4) == 0)
        return enUNDO;
    else if (strncmp(userInput, "redo", 4) == 0)
        return enREDO;
    else if (strncmp(userInput, "exit", 4) == 0)
        return enEXIT;
    else if (strncmp(userInput, "save", 4) == 0)
        return enSAVE;
    else
        return enPLAY;
}
char *readUserInput()
{
    char *inputBuffer = (char *)malloc(sizeof(char) * MAX_INPUT_LENGTH);

    scanf("%s", inputBuffer);

    char userInput;
    if (inputBuffer[0] != '\n')
        return inputBuffer;
    else
        return inputBuffer + 1;
}
bool yesOrNo(char *message)
{
    char *userInput;
    char userChar;
    printf(BHRED "\t\t\t\t\t%s" RESET, message);
    do
    {
        userInput = readUserInput();
        userChar = userInput[0];
        userChar = tolower(userChar);
    } while (userChar != 'y' && userChar != 'n');

    if (userChar == 'y')
        return true;
    return false;
}

//* Handling User Input
char performUserInput(char *userInput, Grid *gameGrid, GameState *currentGame, MovesHistory *movesHistory, Player *player1, Player *player2)
{
    switch (getUserAction(userInput))
    {
        {
        case enUNDO:
            if (currentGame->versusComputer)
            {
                while (movesHistory->moves[movesHistory->currentMove].playerSymbol != PLAYER1)
                {
                    if (undo(gameGrid, movesHistory, currentGame) == SUCCESS)
                        return SUCCESS;
                }
                undo(gameGrid, movesHistory, currentGame);
                return SUCCESS;
            }
            else
            {
                undo(gameGrid, movesHistory, currentGame);
                return SUCCESS;
            }
        case enREDO:
            if (currentGame->versusComputer)
            {
                while (movesHistory->moves[movesHistory->currentMove].playerSymbol != PLAYER1)
                {
                    if (redo(gameGrid, movesHistory, currentGame) == SUCCESS)
                        return SUCCESS;
                }
                redo(gameGrid, movesHistory, currentGame);

                return SUCCESS;
            }
            else
            {
                redo(gameGrid, movesHistory, currentGame);
                return SUCCESS;
            }
        case enSAVE:
            return saveGame(gameGrid, currentGame, movesHistory, player1, player2) ? SUCCESS : FAILURE;
        case enEXIT:
            if(yesOrNo("Are you sure you want to exit without saving [Y/N]: "))
                exit(0);
            return SUCCESS;
        case enPLAY:
            if (isValidGridInput(userInput[0], gameGrid->size))
            {
                if (currentGame->CurrentTurn == PLAYER1)
                    return updateGridWithUserInput(gameGrid, PLAYER1, currentGame, userInput[0], movesHistory, false);
                else
                    return updateGridWithUserInput(gameGrid, PLAYER2, currentGame, userInput[0], movesHistory, false);
            }
            else
            {
                printf("\t\t\t\t\t" REDHB "Input not in Grid:" RESET " ");
                return FAILURE;
            }
        default:
            return FAILURE;
        }
    }
}
void handleUserInput(Grid *gameGrid, GameState *currentGame, MovesHistory *movesHistory, Player *player1, Player *player2)
{
    char userInput;
    char *inputBuffer;
    do
    {
        inputBuffer = readUserInput();
        userInput = performUserInput(inputBuffer, gameGrid, currentGame, movesHistory, player1, player2);
    } while (userInput == FAILURE);
    free(inputBuffer);
}


char updateGridWithUserInput(Grid *gameGrid, char playerSymbol, GameState *currentGame, char userInput, MovesHistory *movesHistory, bool isRedo)
{
    Move move;
    while (1)
    {
        for (int i = 0; i < gameGrid->size; i++)
            if (i % 2 == 0)
            {
                for (int j = 1; j < gameGrid->size; j += 2)
                    if (gameGrid->grid[i][j] == userInput)
                    {
                        addMoveToHistory(i, j, userInput, playerSymbol, movesHistory, isRedo);
                        gameGrid->grid[i][j] = playerSymbol;
                        (currentGame->remainingLines)--;
                        checkBoxesAroundLine(i, j, gameGrid, playerSymbol, currentGame);
                        return SUCCESS;
                    }
            }
            else
                for (int j = 0; j < gameGrid->size; j += 2)
                    if (gameGrid->grid[i][j] == userInput)
                    {
                        addMoveToHistory(i, j, userInput, playerSymbol, movesHistory, isRedo);
                        gameGrid->grid[i][j] = playerSymbol;
                        (currentGame->remainingLines)--;
                        checkBoxesAroundLine(i, j, gameGrid, playerSymbol, currentGame);
                        return SUCCESS;
                    }

        printf("   " REDB "Line was chosen before. Please choose another line:" RESET " ");
        return FAILURE;
    }
}

