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
            if ((gameGrid.grid[row][j + 1] == '1') || (gameGrid.grid[row][j + 1] == '2'))
                printf(BHGRN "%c" RESET, gameGrid.grid[row][j]);
            else
                printf(BHGRN "%-5c" RESET, gameGrid.grid[row][j]);
        else
        {
            switch (gameGrid.grid[row][j])
            {
            case '1':
                printf(BHBLU);
                for (int k = 0; k < 9; k++)
                    printf("%c", DASH);
                printf(RESET);
                break;
            case '2':
                printf(BHRED);
                for (int k = 0; k < 9; k++)
                    printf("%c", DASH);
                printf(RESET);
                break;
            default:
                printf(BHYEL "%-5c" RESET, gameGrid.grid[row][j]);
            }
        }
}
void printOddRows(Grid gameGrid, int row)
{
    for (int line = 0; line <= 2; line++)
    {
        if (line % 2 == 0)
        {
            for (int j = 0; j < gameGrid.size; j++)
                if ((gameGrid.grid[row][j] == '1') || (gameGrid.grid[row][j] == '2'))
                {
                    switch (gameGrid.grid[row][j])
                    {
                    case '1':
                        printf(BHBLU "%-10c" RESET, '|');
                        break;
                    case '2':
                        printf(BHRED "%-10c" RESET, '|');
                        break;
                    }
                }
                else
                    printf("%-5c", ' ');
        }
        else
            for (int j = 0; j < gameGrid.size; j++)
                if (j % 2 == 0)
                    if ((gameGrid.grid[row][j] == '1') || (gameGrid.grid[row][j] == '2'))
                    {
                        switch (gameGrid.grid[row][j])
                        {
                        case '1':
                            printf(BHBLU "%-10c" RESET, '|');
                            break;
                        case '2':
                            printf(BHRED "%-10c" RESET, '|');
                            break;
                        }
                    }
                    else
                        printf(BHYEL "%-10c" RESET, gameGrid.grid[row][j]);
        printf("\n");
    }
}
void printGrid(Grid gameGrid)
{
    printf("\n\n");

    for (int i = 0; i < gameGrid.size; i++)
        if (i % 2 == 0)
            printEvenRows(gameGrid, i);
        else
        {
            printf("\n");
            printOddRows(gameGrid, i);
        }

    printf("\n\n");
}

Grid createGrid(unsigned char size)
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
    for (int i = 0; i < gameGrid->size; i++)
        free(gameGrid->grid[i]);

    free(gameGrid->grid);
}

int main()
{
    unsigned char size = 9;
    Grid gameGrid = createGrid(size);

    initializeGrid(&gameGrid);
    gameGrid.grid[0][1] = '1';
    gameGrid.grid[2][1] = '2';

    gameGrid.grid[3][2] = '1';
    gameGrid.grid[1][4] = '2';
    gameGrid.grid[1][2] = '2';
    printGrid(gameGrid);

    freeGrid(&gameGrid);

    return 0;
}
