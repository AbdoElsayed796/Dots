#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "grid.h"
#define MAX_INPUT_LENGTH 50

bool isValidGridInput(char userInput, char gridSize)//* validate user input based on grid size

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
    fgets(inputBuffer, MAX_INPUT_LENGTH, stdin);

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

int main()
{
    unsigned char size = 5;
    Grid gameGrid = createGrid(size);
    initializeGrid(&gameGrid);
    printGrid(gameGrid);

    char input = getUserInput(size);
    printf("\n%d\n", input);
    char input1 = getUserInput(size);
    printf("\n%d\n", input1);
    // gameGrid.grid[0][1] = PLAYER1;
    // gameGrid.grid[2][1] = PLAYER2;
    // gameGrid.grid[1][0] = PLAYER2;
    // gameGrid.grid[0][3] = PLAYER2;

    // gameGrid.grid[1][4] = PLAYER2;
    // gameGrid.grid[3][2] = PLAYER1;
    // gameGrid.grid[1][2] = PLAYER2;
    // gameGrid.grid[1][1] = PLAYER2;
    // gameGrid.grid[1][3] = PLAYER2;
    // gameGrid.grid[3][1] = PLAYER2;
    // gameGrid.grid[1][5] = PLAYER1;
    // gameGrid.grid[1][6] = PLAYER2;

    freeGrid(&gameGrid);

    return 0;
}