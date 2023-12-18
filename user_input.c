#include <stdio.h>
#include <stdbool.h>
#include "grid.h"

unsigned char getUserInput()
{
    char userInput;
    userInput = getchar();
    
    if (userInput == '\n')
        userInput = getchar();

    bool inputInGrid = (userInput >= '0' && userInput <= '9') ||
                       (userInput >= 'A' && userInput <= 'Z') ||
                       (userInput >= 'a' && userInput <= 'z');
    
    while (!inputInGrid)
    {
        printf("Please, choose a character from the grid!\n");
        userInput = getchar();
        
        if (userInput == '\n')
            userInput = getchar();
        
        inputInGrid = (userInput >= '0' && userInput <= '9') ||
                      (userInput >= 'A' && userInput <= 'Z') ||
                      (userInput >= 'a' && userInput <= 'z');
    }
    return userInput;
}

int main()
{
    unsigned char size = 5;
    // Grid gameGrid = createGrid(size);
    char input = getUserInput();
    printf("\n%d\n", input);
    char input1 = getUserInput();
    printf("\n%d\n", input1);
    // initializeGrid(&gameGrid);
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

    // printGrid(gameGrid);

    // freeGrid(&gameGrid);

    return 0;
}