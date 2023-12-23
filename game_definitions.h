#include<stdbool.h>
#pragma once

#define MAX_INPUT_LENGTH 50
#define MAX_NAME_LENGTH 50
#define DOT '*'
#define DASH '-'
#define PLAYER1 1
#define PLAYER2 2
typedef char SmallNumber;

typedef enum
{
    enPLAYER_1 = PLAYER1,
    enPLAYER_2 = PLAYER2,
} CurrentTurn;
typedef struct
{
    unsigned char **grid;
    SmallNumber size;
} Grid;
typedef struct
{
    int scoreOfPlayer1;
    int scoreOfPlayer2;
    int remainingLines;
    int remainingBoxes;
    CurrentTurn CurrentTurn;

} gameState;
typedef struct
{
    char name[MAX_NAME_LENGTH];
    int score;
    char symbol;
    bool isHuman; // Flag indicating if the player is controlled by a human or AI
    // Add other relevant members as needed...
} Player;