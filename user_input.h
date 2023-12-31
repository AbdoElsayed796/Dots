#pragma once
#include<time.h>
#include <stdbool.h>
#include "game_definitions.h"

void handleUserInput(Grid *gameGrid, GameState *currentGame, MovesHistory *movesHistory, Player *player1, Player *player2);
char updateGridWithUserInput(Grid *gameGrid, char playerSymbol, GameState *currentGame, char userInput, MovesHistory *movesHistory, bool isRedo);
