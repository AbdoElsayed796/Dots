#include <stdio.h>
#include <stdlib.h>
#include "ansi_colors.h"

#define DOT '*'
#define DASH '-'
#define PLAYER1 1
#define PLAYER2 2
typedef struct
{
    unsigned char **grid;
    unsigned char size;
} Grid;

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
                if (ch > 'A')
                    ch = (ch == 'Z') ? 'a' : ch + 1;
                else
                    ch = (ch == '9') ? 'A' : ch + 1;
            }
}

void printEvenRows(Grid gameGrid, int row)
{
    for (int j = 0; j < gameGrid.size; j++)
        if (j % 2 == 0)
            if ((gameGrid.grid[row][j + 1] == PLAYER1) || (gameGrid.grid[row][j + 1] == PLAYER2))
                printf(BHGRN "%c" RESET, gameGrid.grid[row][j]);
            else
                printf(BHGRN "%-5c" RESET, gameGrid.grid[row][j]);
        else
        {
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
}
void printOddRows(Grid gameGrid, int row)
{
    for (int line = 0; line <= 2; line++)
    {
        if (line % 2 == 0)
        {
            printf("\t\t\t");
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
                    if (j % 2 == 0)
                        if ((gameGrid.grid[row][j] == PLAYER1) || (gameGrid.grid[row][j] == PLAYER2))
                            printf("%-9c", ' ');
                        else
                            printf("%-10c", ' ');
                }
            }
        }
        else
        {
            printf("\t\t\t");
            for (int j = 0; j < gameGrid.size; j++)
                if (j % 2 == 0)
                {
                    if ((gameGrid.grid[row][j] == PLAYER1) || (gameGrid.grid[row][j] == PLAYER2))
                    {
                        switch (gameGrid.grid[row][j])
                        {
                        case PLAYER1:
                            printf(BHBLU "%-5c" RESET, '|');
                            break;
                        case PLAYER2:
                            printf(BHRED "%-5c" RESET, '|');
                            break;
                        }
                    }
                    else
                        printf(BHYEL "%-5c" RESET, gameGrid.grid[row][j]);
                }
                else
                {
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
        printf("\n");
    }
}
void printGrid(Grid gameGrid)
{
    printf("\n\n");

    for (int i = 0; i < gameGrid.size; i++)
        if (i % 2 == 0)
        {
            printf("\t\t\t");
            printEvenRows(gameGrid, i);
        }
        else
        {
            printf("\t\t\t");
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
    unsigned char size = 11;
    Grid gameGrid = createGrid(size);

    initializeGrid(&gameGrid);
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
    printGrid(gameGrid);

    freeGrid(&gameGrid);

    return 0;
}