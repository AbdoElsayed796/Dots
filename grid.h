#pragma once

#define DOT '*'
#define DASH '-'
#define PLAYER1 1
#define PLAYER2 2

typedef struct
{
    unsigned char **grid;
    unsigned char size;
} Grid;

void initializeGrid(Grid *gameGrid);
void printGrid(Grid* gameGrid);
Grid createGrid(unsigned char size);
void freeGrid(Grid *gameGrid);