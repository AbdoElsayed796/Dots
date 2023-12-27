#pragma once
#include "game_logic.h"

void undo(Grid *gameGrid, MovesHistory *movesHistory, GameState *currentGame);
void undoLine(Grid *gameGrid, MovesHistory *movesHistory, GameState *currentGame);
void undoBox(Grid *gameGrid, MovesHistory *movesHistory, GameState *currentGame);
void undoGameState(MovesHistory *movesHistory,GameState *currentGame,int numberOfBoxesOPend,char symbol);
void redo(Grid *gameGrid, MovesHistory *movesHistory,GameState *currentGame);
