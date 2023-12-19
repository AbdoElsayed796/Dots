#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "user_input.h"

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
unsigned char getUserInput(char gridSize)
{
    char inputBuffer[MAX_INPUT_LENGTH];
    scanf("%s", inputBuffer);

    char userInput;
    if (inputBuffer[0] != '\n')
        userInput = inputBuffer[0];
    else
        userInput = inputBuffer[1];

    bool inputInGrid = isValidGridInput(userInput, gridSize);
    while (!inputInGrid)
    {
        printf("Please, choose a character from the grid!\n");
        fgets(inputBuffer, MAX_INPUT_LENGTH, stdin);

        if (inputBuffer[0] != '\n')
            userInput = inputBuffer[0];
        else
            userInput = inputBuffer[1];

        inputInGrid = isValidGridInput(userInput, gridSize);
    }
    return userInput;
}

void updateGridWithUserInput(Grid *gameGrid, Player currentTurn, char userInput)
{
    bool charFound = false;
    while (!charFound)
    {
        for (int i = 0; i < gameGrid->size; i++)
            if (i % 2 == 0)
            {
                for (int j = 1; j < gameGrid->size; j += 2)
                    if (gameGrid->grid[i][j] == userInput)
                    {
                        gameGrid->grid[i][j] = currentTurn.symbol;
                        charFound = true;
                        return;
                    }
            }
            else
                for (int j = 0; j < gameGrid->size; j += 2)
                    if (gameGrid->grid[i][j] == userInput)
                    {
                        gameGrid->grid[i][j] = currentTurn.symbol;
                        charFound = true;
                        return;
                    }

        if (!charFound)
        {
            printf("\nLine was chosen before. Please choose another line.\n");
            userInput = getUserInput(gameGrid->size);
        }
    }
}