#pragma once
#include<time.h>
#include <stdbool.h>
#include "game_definitions.h"

unsigned char getUserInput(char gridSize);
void updateGridWithUserInput(Grid *gameGrid, Player currentTurn,GameState *currentGame, char userInput,gameTurn *ptrTurn);