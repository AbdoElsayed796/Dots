#include <stdio.h>
#include "ansi_colors.h"
#include "initialization.h"

#define DASH '-'
#define DOT '.'

void initializeGrid(GameGridExpert *gameGrid)
{

    for (int i = 0; i < 25; i++)
        for (int j = 0; j < 25; j++)
            if (i % 6 == 0 && j % 6 == 0)
            {
                gameGrid->outputGrid[i][j] = DOT; // Place DOT symbol at multiples of 6 in both i and j

                if (j < 24)
                    for (int k = 1; k <= 5; k++)
                    {
                        gameGrid->outputGrid[i][j + k] = DASH; // Draw horizontal dashes
                        gameGrid->outputGrid[j + k][i] = '|';  // Draw vertical lines
                    }
            }
            else
                gameGrid->outputGrid[i][j] = ' '; // Fill other positions with space character

    char ch = 'A'; // Initialize character 'ch' to 'A'  

    // Populate the grid with characters at specific positions
    for (int i = 0; i < 25; i += 6)
        for (int j = 0; j < 25; j += 6)
        {
            if (i + (6 / 2) < 25)
            {
                // Place character in the center horizontally
                gameGrid->outputGrid[i + (6 / 2)][j] = ch;
                ch = (ch == 'Z') ? 'a' : ch + 1;
            }
            if (j + (6 / 2) < 25)
            {
                // Place character in the center vertically
                gameGrid->outputGrid[i][j + (6 / 2)] = ch;
                ch = (ch == 'Z') ? 'a' : ch + 1;
            }
        }
}

void printGrid(unsigned char gameGrid[25][25])
{

    // Display the grid with formatted characters
    printf("\n\n\n\n");
    for (int i = 0; i < 25; i++)
    {
        for (int j = 0; j < 25; j++)
            switch (gameGrid[i][j])
            {
            case ' ':
                printf(BLK "%c " RESET, gameGrid[i][j]);
                break;
            case DOT:
                printf(BHGRN "%c " RESET, gameGrid[i][j]);
                break;
            case '|':
                printf(HBLK "  " RESET, gameGrid[i][j]);
                break;
            case DASH:
                printf(HBLK "  " RESET, gameGrid[i][j]);
                break;
            default:
                printf(HMAG "%c " RESET, gameGrid[i][j]);
                break;
            }
        printf("\n");
    }
    printf("\n\n\n\n");
}

int main()
{
    unsigned char game[25][25];

    GameGridExpert S;
    initializeGrid(&S);
    printGrid(S.outputGrid);

    return 0;
}