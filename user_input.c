#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "ansi_colors.h"
#include "game_logic.h"
#include "undo_redo.h"
#include "game_definitions.h"

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
    else
        return enPLAY;
}

char *readUserInput()
{
    static char inputBuffer[MAX_INPUT_LENGTH];
    scanf("%s", inputBuffer);

    char userInput;
    if (inputBuffer[0] != '\n')
        return inputBuffer;
    else
        return inputBuffer + 1;
}

char performUserInput(char *userInput, Grid *gameGrid, char playerSymbol, GameState *currentGame, MovesHistory *movesHistory)
{
    switch (getUserAction(userInput))
    {
        {
        case enUNDO:
            if(currentGame->versusComputer){
            undo(gameGrid, movesHistory, currentGame);
            undo(gameGrid, movesHistory, currentGame);
            return SUCCESS;
            }
            else
            {
             undo(gameGrid, movesHistory, currentGame);
            return SUCCESS;
            }       
        case enREDO:
            if(currentGame->versusComputer){
            redo(gameGrid, movesHistory, currentGame);
            redo(gameGrid, movesHistory, currentGame);
            return SUCCESS;
            }
            else
            {
             redo(gameGrid, movesHistory, currentGame);
             return SUCCESS;
            }       
        case enEXIT:
            // exit();
            return SUCCESS;
        case enPLAY:
            if (isValidGridInput(userInput[0], gameGrid->size))
                return updateGridWithUserInput(gameGrid, playerSymbol, currentGame, userInput[0], movesHistory);
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

void handleUserInput(Grid *gameGrid, char playerSymbol, GameState *currentGame, MovesHistory *movesHistory)
{
    char userInput;
    do
    {
        userInput = performUserInput(readUserInput(), gameGrid, playerSymbol, currentGame, movesHistory);
    } while (userInput == FAILURE);
}

char updateGridWithUserInput(Grid *gameGrid, char playerSymbol, GameState *currentGame, char userInput, MovesHistory *movesHistory)
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
                        addMoveToHistory(i, j, userInput, playerSymbol, movesHistory);
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
                        addMoveToHistory(i, j, userInput, playerSymbol, movesHistory);
                        gameGrid->grid[i][j] = playerSymbol;
                        (currentGame->remainingLines)--;
                        checkBoxesAroundLine(i, j, gameGrid, playerSymbol, currentGame);
                        return SUCCESS;
                    }

        printf("   " REDB "Line was chosen before. Please choose another line:" RESET " ");
        return FAILURE;
    }
}