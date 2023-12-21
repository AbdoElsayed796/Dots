
#pragma once

#define DOT '*'
#define DASH '-'
#define PLAYER1 1
#define PLAYER2 2
#define BEGINNER_SIZE 5
#define EXPERT_SIZE 11
typedef char SmallNumber;

typedef struct
{
    unsigned char **grid;
    SmallNumber size;
} Grid;
typedef struct
{
 int scoreOfPlayer1;
 int scoreOfPlayer2;
 int remainingLines;
 int remainingBoxes;

}gameCounts;
void initializeGrid(Grid *gameGrid);
void printGrid(Grid gameGrid,gameCounts *currentGame);
Grid createGrid(SmallNumber size);
void freeGrid(Grid *gameGrid); // Deallocate memory used by the game grid
