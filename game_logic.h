#pragma once
#include "grid.h"
#include "user_input.h"

SmallNumber countBoxSides(int i, int j, Grid *gameGrid);
void markBoxSides(int i, int j, Grid *gameGrid, char playerSymbol);
bool checkAndMarkClosedBox(int i, int j, Grid *gameGrid, char playerSymbol, GameState *currentGame);
void checkBoxesAroundLine(int i, int j, Grid *gameGrid, char playerSymbol,GameState *currentGame);
void getTimeDiff(SmallNumber *minDiff, SmallNumber *secDiff);