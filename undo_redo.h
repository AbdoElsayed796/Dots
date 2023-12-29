#pragma once

void undo(Grid *gameGrid, MovesHistory *movesHistory, GameState *currentGame);
void redo(Grid *gameGrid, MovesHistory *movesHistory, GameState *currentGame);
void addMoveToHistory(SmallNumber i, SmallNumber j, char oldValue, char playerSymbol, MovesHistory *movesHistory);