#include <stdio.h>
#include "ANSI_COLORS.h"
#include "Initialization.c"
#define DASH '-'
#define DOT '.'

void printGridExpert(struct GameGridExpert gameGrid)
{

    for (int i = 0; i < 25; i++)
    {

        for (int j = 0; j < 25; j++)
        {
            if (i % 6 == 0 && j % 6 == 0)
            {
                gameGrid.outputGrid[i][j] = DOT;
            }
            else
                gameGrid.outputGrid[i][j] = ' ';
        }
    }
    for (int i = 0; i < 25; i++)
    {
        for (int j = 0; j < 25; j++)
        {
            if (i % 6 == 0 && j % 6 == 0 && j < 24)
            {
                for (int k = 1; k <= 5; k++)
                {
                    gameGrid.outputGrid[i][j + k] = DASH;
                    gameGrid.outputGrid[j + k][i] = '|';
                }
            }
        }
    }

    char a = 'A';
    // Place '1' in the middle of the distance between adjacent '*'
    for (int i = 0; i < 25; i++)
    {
        for (int j = 0; j < 25; j++)
        {
            if (i % 6 == 0 && j % 6 == 0)
            {
                // Check if there is room to place '1' between adjacent '*'
                if (i + 6 < 25)
                {
                    gameGrid.outputGrid[i + 6 / 2][j] = a;
                    if (a == 'Z')
                        a = 'a';
                    else
                        a++;
                }
                if (j + 6 < 25)
                {
                    gameGrid.outputGrid[i][j + 6 / 2] = a;
                    if (a == 'Z')
                        a = 'a';
                    else
                        a++;
                }
            }
        }
    }

    printf("\n\n\n\n");
    for (int i = 0; i < 25; i++)
    {
        for (int j = 0; j < 25; j++)
        {
            if (gameGrid.outputGrid[i][j] == ' ')
                printf(RED "%c ", gameGrid.outputGrid[i][j]);
            else if (gameGrid.outputGrid[i][j] == DOT)
                printf(RED "%c ", gameGrid.outputGrid[i][j]);
            else if (gameGrid.outputGrid[i][j] == '|')
                printf(MAGENTA "  ", gameGrid.outputGrid[i][j]);
            else if (gameGrid.outputGrid[i][j] == DASH)
                printf(MAGENTA "  ", gameGrid.outputGrid[i][j]);
            else if (gameGrid.outputGrid[i][j] == '-')
                printf("  ");
            else
                printf(GREEN "%c ", gameGrid.outputGrid[i][j]);
        }
        printf("\n");
    }
    printf("\n\n\n\n");
}
int main()
{
    struct GameGridExpert game;
    printGridExpert(game);

    return 0;
}
