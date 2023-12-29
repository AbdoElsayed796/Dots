#pragma once
#include<time.h>
#include <stdbool.h>
#include "game_definitions.h"

void handleUserInput(Grid *gameGrid, char playerSymbol, GameState *currentGame, MovesHistory *movesHistory);
char updateGridWithUserInput(Grid *gameGrid, char playerSymbol, GameState *currentGame, char userInput, MovesHistory *movesHistory);
