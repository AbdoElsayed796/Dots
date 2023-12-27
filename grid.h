#pragma once
#include "game_definitions.h"

void initializeGrid(Grid *gameGrid);
void printGrid(Grid gameGrid,GameState *currentGame);
Grid createGrid(SmallNumber size);
void freeGrid(Grid *gameGrid); // Deallocate memory used by the game grid
void clearConsole();
void turns(Grid *gameGrid, GameState *currentGame, int remainingLines,MovesHistory *moveHistory);