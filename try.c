#include <stdio.h>
#include <stdlib.h>
#include "ansi_colors.h"

#define DOT '.'
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

void printGrid(Grid gameGrid)
{
    printf("\n\n");

    for (int i = 0; i < gameGrid.size; i++)
    {
        if (i % 2 == 0)
            for (int j = 0; j < gameGrid.size; j++)
                if (j % 2 == 0)
                    if (gameGrid.grid[i][j + 1] == DASH)
                        printf(BHGRN "%c" RESET, gameGrid.grid[i][j]);
                    else
                        printf(BHGRN "%-6c" RESET, gameGrid.grid[i][j]);
                else if(gameGrid.grid[i][j] == DASH)
                {
                    printf(HWHT);
                    for (int k = 0; k < 11; k++)
                        printf("%c", gameGrid.grid[i][j]);
                    printf(RESET);
                }
                else
                    printf(HMAG "%-6c" RESET, gameGrid.grid[i][j]);
        else
        {
            
            printf("\n");
                for (int j = 0; j < gameGrid.size; j++)
                {
                    if (j % 2 == 0)
                    {
                        if (gameGrid.grid[i][j] == '|')
                        {
                            printf(HWHT "%-12c", '|');
                        }
                        else
                            printf("%-12c", ' ');
                    }
                }
            printf("\n");
            for (int j = 0; j < gameGrid.size; j++)
            {
                if (j % 2 == 0)
                {
                    if (gameGrid.grid[i][j] == '|')
                    {
                        printf(HWHT "%-12c", '|');
                    }
                    else
                    {
                        printf(HMAG "%-12c" RESET, gameGrid.grid[i][j]);
                    }
                }
            }
            printf("\n");
            for (int j = 0; j < gameGrid.size; j++)
            {
                if (j % 2 == 0)
                {
                    if (gameGrid.grid[i][j] == '|')
                    {
                        printf(HWHT "%-12c", '|');
                    }
                    else
                        printf("%-12c", ' ');
                }
            }
            printf("\n");
        }
    }

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
    unsigned char size = 5; // 57
    Grid gameGrid = createGrid(size);

    initializeGrid(&gameGrid);
    // gameGrid.grid[0][1] = DASH;
    gameGrid.grid[3][2] = '|'; //
    printGrid(gameGrid);

    freeGrid(&gameGrid);

    return 0;
}
