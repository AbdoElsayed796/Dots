#pragma once
#include "grid.h"
#include "user_input.h"

void turns(Grid *gameGrid, GameState *currentGame, int remainingLines,gameTurn *ptrTurn);
SmallNumber countBoxSides(int i, int j, Grid *gameGrid);
void markBoxSides(int i, int j, Grid *gameGrid, char playerSymbol);
bool checkAndMarkClosedBox(int i, int j, Grid *gameGrid, char playerSymbol, GameState *currentGame);
void checkBoxesAroundLine(int i, int j, Grid *gameGrid, char playerSymbol, GameState *currentGame);