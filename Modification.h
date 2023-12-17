#include <stdio.h>
#include "ANSI_COLORS.h"
#include "Initialization.h"
#define DASH '-'
#define DOT '.'

#ifndef MODIFICATION_H_INCLUDED
#define MODIFICATION_H_INCLUDED
void PrintAfterModificationExpert(GameGridExpert *Game)
{
    for (int i = 0; i < 25; i++)
    {
        for (int j = 0; j < 25; j++)
        {
            if (Game->outputGrid[i][j] == ' ')
                printf(RED "%c ", Game->outputGrid[i][j]);
            else if (Game->outputGrid[i][j] == DOT)
                printf(RED "%c ", Game->outputGrid[i][j]);
            else if (Game->outputGrid[i][j] == '|')
                printf(MAGENTA "%c ", Game->outputGrid[i][j]);
            else if (Game->outputGrid[i][j] == DASH)
                printf(MAGENTA "%c ", Game->outputGrid[i][j]);
            else if (Game->outputGrid[i][j] == '-')
                printf("  ");
            else
                printf(GREEN "%c ", Game->outputGrid[i][j]);
        }
        printf("\n");
    }
    printf("\n\n\n\n");
}
void PrintAfterModificatioBeginner(GameGridExpert Game)
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (Game.outputGrid[i][j] == ' ')
                printf(RED "%c ", Game.outputGrid[i][j]);
            else if (Game.outputGrid[i][j] == DOT)
                printf(RED "%c ", Game.outputGrid[i][j]);
            else if (Game.outputGrid[i][j] == '|')
                printf(MAGENTA "%c ", Game.outputGrid[i][j]);
            else if (Game.outputGrid[i][j] == DASH)
                printf(MAGENTA "%c ", Game.outputGrid[i][j]);
            else
                printf(GREEN "%c ", Game.outputGrid[i][j]);
        }
        printf("\n");
    }
    printf("\n\n\n\n");
}

void ModificationExpert(GameGridExpert *Game, char X)
{
     for (int i = 0; i < 25; i++)
    {
        for (int j = 0; j < 25; j++)
        {
            if (Game->outputGrid[i][j] == X && j < 24)
            {
                if (Game->outputGrid[i][j + 1] == '-')
                {
                    Game->outputGrid[i][j] = '-';
                }
                else
                {
                    Game->outputGrid[i][j] = '|';
                }
            }
            else if (Game->outputGrid[i][j] == X && j == 24)
                Game->outputGrid[i][j] = '|';
        }
    }
    PrintAfterModificationExpert(Game);
}
void ModificationBeginner(GameGridBeginner Game, char X)
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (Game.outputGrid[i][j] == X && j < 8)
            {
                if (Game.outputGrid[i][j + 1] == '-')
                {
                    Game.outputGrid[i][j] = '-';
                }
                else
                {
                    Game.outputGrid[i][j] = '|';
                }
            }
            else if (Game.outputGrid[i][j] == X && j == 8)
                Game.outputGrid[i][j] = '|';
        }
    }
  //  PrintAfterModificatioBeginner(Game, color);
}

#endif