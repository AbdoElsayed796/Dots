#include <stdio.h>
#include "ansi_colors.h"
#include "Initialization.h"
#define DASH '-'
#define DOT '.'

#ifndef PRINTGIDE_H_INCLUDED
#define PRINTGIDE_H_INCLUDED

<<<<<<< HEAD
void PrintGridExpert(GameGridExpert *gameGrid)
{    
    for(int i=0; i < 9 ; i++)
    {
      for(int j=0; j < 9 ; j++)
      {
        gameGrid->DataGrid[i][j]=' ';
      }
=======
void PrintGridExpert(GameGridExpert gameGrid)
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            gameGrid.DataGrid[i][j] = ' ';
        }
>>>>>>> 877fdd9d67d9a48930b00ef90a6368c90ce61906
    }

    for (int i = 0; i < 25; i++)
    {

        for (int j = 0; j < 25; j++)
        {
            if (i % 6 == 0 && j % 6 == 0)
            {
                gameGrid->outputGrid[i][j] = DOT;
            }
            else
                gameGrid->outputGrid[i][j] = ' ';
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
                    gameGrid->outputGrid[i][j + k] = DASH;
                    gameGrid->outputGrid[j + k][i] = '|';
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
                    gameGrid->outputGrid[i + 6 / 2][j] = a;
                    if (a == 'Z')
                        a = 'a';
                    else
                        a++;
                }
                if (j + 6 < 25)
                {
                    gameGrid->outputGrid[i][j + 6 / 2] = a;
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
                printf(BLK "%c " RESET, gameGrid.outputGrid[i][j]);
            else if (gameGrid.outputGrid[i][j] == DOT)
                printf(BHGRN "%c " RESET, gameGrid.outputGrid[i][j]);
            else if (gameGrid.outputGrid[i][j] == '|')
                printf(HBLK "  " RESET, gameGrid.outputGrid[i][j]);
            else if (gameGrid.outputGrid[i][j] == DASH)
                printf(HBLK "  " RESET, gameGrid.outputGrid[i][j]);
            else if (gameGrid.outputGrid[i][j] == '-')
                printf("  ");
            else
                printf(HMAG "%c " RESET, gameGrid.outputGrid[i][j]);
        }
        printf("\n");
    }
    printf("\n\n\n\n");
}

void PrintGridBeginner(GameGridBeginner gameGrid)
{

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            gameGrid.DataGrid[i][j] = ' ';
        }
    }

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (i % 4 == 0 && j % 4 == 0)
            {
                gameGrid.outputGrid[i][j] = DOT;
            }
            else
                gameGrid.outputGrid[i][j] = ' ';
        }
    }
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (i % 4 == 0 && j % 4 == 0 && j < 8)
            {
                for (int k = 1; k <= 3; k++)
                {
                    gameGrid.outputGrid[i][j + k] = DASH;
                    gameGrid.outputGrid[j + k][i] = '|';
                }
            }
        }
    }

    char a = 'A';
    // Place '1' in the middle of the distance between adjacent '*'
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (i % 4 == 0 && j % 4 == 0)
            {
                // Check if there is room to place '1' between adjacent '*'
                if (i + 4 < 9)
                {
                    gameGrid.outputGrid[i + 4 / 2][j] = a;
                    if (a == 'Z')
                        a = 'a';
                    else
                        a++;
                }
                if (j + 4 < 9)
                {
                    gameGrid.outputGrid[i][j + 4 / 2] = a;
                    if (a == 'Z')
                        a = 'a';
                    else
                        a++;
                }
            }
        }
    }
    printf("\n\n\n\n");
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (gameGrid.outputGrid[i][j] == ' ')
                printf(BLK "%c " RESET, gameGrid.outputGrid[i][j]);
            else if (gameGrid.outputGrid[i][j] == DOT)
                printf(BHGRN "%c " RESET, gameGrid.outputGrid[i][j]);
            else if (gameGrid.outputGrid[i][j] == '|')
                printf(HBLK "  " RESET, gameGrid.outputGrid[i][j]);
            else if (gameGrid.outputGrid[i][j] == DASH)
                printf(HBLK "  " RESET, gameGrid.outputGrid[i][j]);
            else if (gameGrid.outputGrid[i][j] == '-')
                printf("  ");
            else
                printf(HMAG "%c " RESET, gameGrid.outputGrid[i][j]);
        }
        printf("\n");
    }
    // printf("\n\n\n\n");
}
#endif
