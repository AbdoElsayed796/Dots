#pragma once

char undo(Grid *gameGrid, MovesHistory *movesHistory, GameState *currentGame);
char redo(Grid *gameGrid, MovesHistory *movesHistory, GameState *currentGame);
void addMoveToHistory(SmallNumber i, SmallNumber j, char oldValue, char playerSymbol, MovesHistory *movesHistory, bool isRedo);
