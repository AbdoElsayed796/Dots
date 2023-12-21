#pragma once
#include <stdbool.h>
#include "grid.h"
#define MAX_INPUT_LENGTH 50
#define MAX_NAME_LENGTH 50

typedef struct
{
    char name[MAX_NAME_LENGTH];
    int score;
    char symbol;
    bool isHuman; // Flag indicating if the player is controlled by a human or AI
    // Add other relevant members as needed...
} Player;

unsigned char getUserInput(char gridSize);
void updateGridWithUserInput(Grid *gameGrid, Player currentTurn,gameCounts *currentGame, char userInput);