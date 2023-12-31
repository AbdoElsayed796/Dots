#pragma once
#include <stdio.h>
#include "game_definitions.h"

void readGame(Grid *gameGrid, GameState *currentGame, MovesHistory *movesHistory, Player *player1, Player *player2, char *filename);
bool saveGame(Grid *gameGrid, GameState *currentGame, MovesHistory *movesHistory, Player *player1, Player *player2);
char *openFileAndReadDate(FILE **filePtr, char *filename);
