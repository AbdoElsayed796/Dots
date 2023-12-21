#include <stdio.h>
#include <stdlib.h>
#include "ansi_colors.h"
#include "grid.h" //Include header file defining Grid structure and constants

void initializeGrid(Grid *gameGrid)
{
    unsigned char ch = '0';

    for (int i = 0; i < gameGrid->size; i++)
        for (int j = 0; j < gameGrid->size; j++)
            if ((i % 2 == 0) && (j % 2 == 0))
                gameGrid->grid[i][j] = DOT;
            else if ((i % 2 == 1) && (j % 2 == 1))
                gameGrid->grid[i][j] = ' ';
            else
            {
                gameGrid->grid[i][j] = ch;
                if (ch <= 'A')
                    ch = (ch == '9') ? 'A' : ch + 1;
                else
                    ch = (ch == 'Z') ? 'a' : ch + 1;
            }
}

void printDotsRow(Grid gameGrid, int row)
{
    for (int j = 0; j < gameGrid.size; j++)
        if (j % 2 == 0)
            if ((gameGrid.grid[row][j + 1] == PLAYER1) || (gameGrid.grid[row][j + 1] == PLAYER2))
                printf(BHGRN "%c" RESET, gameGrid.grid[row][j]);
            else
                printf(BHGRN "%-5c" RESET, gameGrid.grid[row][j]);
        else
            switch (gameGrid.grid[row][j])
            {
            case PLAYER1:
                for (int k = 0; k < 9; k++)
                    printf(BHBLU "%c" RESET, DASH);
                break;
            case PLAYER2:
                for (int k = 0; k < 9; k++)
                    printf(BHRED "%c" RESET, DASH);
                break;
            default:
                printf(BHYEL "%-5c" RESET, gameGrid.grid[row][j]);
            }
}

void printVerticalLines(Grid gameGrid, int row)
{
    for (int j = 0; j < gameGrid.size; j++)
    {
        if (j % 2 == 0)
        {
            if ((gameGrid.grid[row][j] == PLAYER1) || (gameGrid.grid[row][j] == PLAYER2))
            {
                switch (gameGrid.grid[row][j])
                {
                case PLAYER1:
                    printf(BHBLU "%c" RESET, '|');
                    break;
                case PLAYER2:
                    printf(BHRED "%c" RESET, '|');
                    break;
                }
            }

            if ((gameGrid.grid[row][j] == PLAYER1) || (gameGrid.grid[row][j] == PLAYER2))
                printf("%-9c", ' ');
            else
                printf("%-10c", ' ');
        }
    }
}

void printCharacterOrBox(Grid gameGrid, int row)
{
    for (int j = 0; j < gameGrid.size; j++)
    {
        if (j % 2 == 0) // print vertical character or whitespace
            if ((gameGrid.grid[row][j] == PLAYER1) || (gameGrid.grid[row][j] == PLAYER2))
                switch (gameGrid.grid[row][j])
                {
                case PLAYER1:
                    printf(BHBLU "%-5c" RESET, '|');
                    break;
                case PLAYER2:
                    printf(BHRED "%-5c" RESET, '|');
                    break;
                }
            else
                printf(BHYEL "%-5c" RESET, gameGrid.grid[row][j]);
        else // print box
            switch (gameGrid.grid[row][j])
            {
            case PLAYER1:
                printf(BHBLU "%-5c" RESET, '1');
                break;
            case PLAYER2:
                printf(BHRED "%-5c" RESET, '2');
                break;
            default:
                printf(BHRED "%-5c" RESET, ' ');
            }
    }
}

void printGrid(Grid gameGrid,gameCounts *currentGame)
{
    printf("\n");
    for (int i = 0; i < gameGrid.size; i++)
    {
        printf("\t\t\t");
        if (i % 2 == 0)
            printDotsRow(gameGrid, i);
        else
        {
            printf("\n");
            for (int line = 0; line <= 2; line++)
            {
                printf("\t\t\t");
                if (line % 2 == 0)
                    printVerticalLines(gameGrid, i);
                else
                    printCharacterOrBox(gameGrid, i);
                printf("\n");
            }
        }
    }
    printf("\n\n");
    printf(MAG"\t\t\tNumber OF Remaining Lines is : %d\n\n"RESET,currentGame->remainingLines);
    printf(GRN"\t\t\tNumber OF Remaining Boxes is : %d\n\n"RESET,currentGame->remainingBoxes);
    printf(BHBLU"\t\t\tPoints Of Player1 is : %d\n\n"RESET,currentGame->scoreOfPlayer1);
    printf(BHRED"\t\t\tPoints OF Player2 is : %d\n\n"RESET,currentGame->scoreOfPlayer2);

}

Grid createGrid(SmallNumber size)
{
    Grid newGrid;
    newGrid.size = size;

    newGrid.grid = (unsigned char **)malloc(size * sizeof(unsigned char *));
    if (newGrid.grid == NULL)
    {
        printf("Memory allocation failed. Exiting...\n");
        exit(1);
    }

    for (int i = 0; i < size; i++)
    {
        newGrid.grid[i] = (unsigned char *)malloc(size * sizeof(unsigned char));
        if (newGrid.grid[i] == NULL)
        {
            printf("Memory allocation failed. Exiting...\n");
            exit(1);
        }
    }

    return newGrid;
}

void freeGrid(Grid *gameGrid)
{
    for (int i = 0; i < gameGrid->size; i++) // Free memory for each row in the grid
        free(gameGrid->grid[i]);

    free(gameGrid->grid); // Free the memory allocated for the grid itself
}