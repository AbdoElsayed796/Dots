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

void initializeGrid(Grid *gameGrid);
void printGrid(Grid gameGrid);
Grid createGrid(SmallNumber size);
void freeGrid(Grid *gameGrid); // Deallocate memory used by the game grid
