#pragma once
#include "game_logic.h"

void undo(gameTurn *ptrTurn, Grid *gameGrid, GameState *currentGame);
void redo (gameTurn *ptrTurn, Grid *gameGrid, GameState *currentGame);