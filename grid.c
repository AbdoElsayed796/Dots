#include <stdio.h>
#include <stdlib.h>
#include "ansi_colors.h"

#define DOT '*'
#define DASH '-'

typedef struct
{
    unsigned char **grid;
    unsigned char size;
} Grid;

void initializeGrid(Grid *gameGrid)
{
    unsigned char ch = 'A';

    for (int i = 0; i < gameGrid->size; i++)
        for (int j = 0; j < gameGrid->size; j++)
            if ((i % 2 == 0) && (j % 2 == 0))
                gameGrid->grid[i][j] = DOT;
            else if ((i % 2 == 1) && (j % 2 == 1))
                gameGrid->grid[i][j] = ' ';
            else
            {
                gameGrid->grid[i][j] = ch;
                ch = (ch == 'Z') ? 'a' : ch + 1;
            }
}

void printEvenRows(Grid gameGrid, int row)
{
    for (int j = 0; j < gameGrid.size; j++)
        if (j % 2 == 0)
            if (gameGrid.grid[row][j + 1] == DASH)
                printf(BHGRN "%c" RESET, gameGrid.grid[row][j]);
            else
                printf(BHGRN "%-5c" RESET, gameGrid.grid[row][j]);
        else if (gameGrid.grid[row][j] == DASH)
        {
            printf(HWHT);
            for (int k = 0; k < 9; k++)
                printf("%c", gameGrid.grid[row][j]);
            printf(RESET);
        }
        else
            printf(HMAG "%-5c" RESET, gameGrid.grid[row][j]);
}
void printOddRows(Grid gameGrid, int row)
{
    for (int line = 0; line <= 2; line++)
    {
        if (line % 2 == 0)
        {
            for (int j = 0; j < gameGrid.size; j++)
                if (j % 2 == 0)
                    if (gameGrid.grid[row][j] == '|')
                        printf(HWHT "%-10c" RESET, '|');
                    else
                        printf("%-10c", ' ');
        }
        else
            for (int j = 0; j < gameGrid.size; j++)
                if (j % 2 == 0)
                    if (gameGrid.grid[row][j] == '|')
                        printf(HWHT "%-10c" RESET, '|');
                    else
                        printf(HMAG "%-10c" RESET, gameGrid.grid[row][j]);
        printf("\n");
    }
}
void printGrid(Grid gameGrid)
{
    printf("\n\n");

    for (int i = 0; i < gameGrid.size; i++)
<<<<<<< HEAD:new_grid_system.c
    {
        for (int j = 0; j < gameGrid.size; j++)
            if ((i % 2 == 0) && (j % 2 == 0))A
                if (gameGrid.grid[i][j + 1] == DASH)
                    printf(BHGRN "%c" RESET, gameGrid.grid[i][j]);
                else
                    printf(BHGRN "%-6c" RESET, gameGrid.grid[i][j]);
            else if (gameGrid.grid[i][j] == DASH)
            {
                printf(HWHT);
                for (int k = 0; k < 11; k++)
                    printf("%c", gameGrid.grid[i][j]);
                printf(RESET);
            }
            else if (gameGrid.grid[i][j] == ' ')
                printf("");
            else if (j % 2 == 0)
                printf(HMAG "%-12c" RESET, gameGrid.grid[i][j]);
            else
                printf(HMAG "%-6c" RESET, gameGrid.grid[i][j]);
        printf("\n\n");
    }
=======
        if (i % 2 == 0)
            printEvenRows(gameGrid, i);
        else
        {
            printf("\n");
            printOddRows(gameGrid, i);
        }

>>>>>>> 6f62461dc08119ef9918497a68a038e1b5648ae1:grid.c
    printf("\n\n");
}

Grid createGrid(unsigned char size)
{
    Grid newGrid;
    newGrid.size = size; // 5

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
    for (int i = 0; i < gameGrid->size; i++)
        free(gameGrid->grid[i]);

    free(gameGrid->grid);
}

int main()
{
    unsigned char size = 9;
    Grid gameGrid = createGrid(size);

    initializeGrid(&gameGrid);
    // gameGrid.grid[0][1] = DASH;
    // gameGrid.grid[3][2] = '|';
    printGrid(gameGrid);

    freeGrid(&gameGrid);

    return 0;
}
