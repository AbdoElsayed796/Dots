#pragma once
#include "game_logic.h"

void undo(gameTurn *ptrTurn, Grid *gameGrid, gameState *currentGame);
void redo (gameTurn *ptrTurn, Grid *gameGrid, gameState *currentGame);