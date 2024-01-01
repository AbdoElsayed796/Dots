#include <stdbool.h>
#pragma once

#define MAX_INPUT_LENGTH 50
#define MAX_NAME_LENGTH 50
#define DOT '+'
#define DASH '-'
#define PLAYER1 1
#define PLAYER2 2
#define FAILURE 0 //! dummy value for failure
#define SUCCESS 3 //! dummy value for success
#define SCOREBOARD_FILE "scoreboard.txt"
#define GAME_1 "game1.bin"
#define GAME_2 "game2.bin"
#define GAME_3 "game3.bin"
#define FORMATTED_DATE_SIZE 25

typedef char SmallNumber;

typedef enum
{
    enPLAYER_1 = PLAYER1,
    enPLAYER_2 = PLAYER2,
} CurrentTurn;

typedef enum
{
    enEXIT = 0,
    enUNDO = 1,
    enREDO = 2,
    enSAVE = 3,
    enPLAY = 4,
    enOTHER = 5
} UserAction;

typedef struct
{
    unsigned char **grid;
    SmallNumber size;
} Grid;
typedef struct
{
    int player1Score;
    int player2Score;
    int remainingLines;
    int remainingBoxes;
    bool versusComputer;
    CurrentTurn CurrentTurn;

} GameState;
typedef struct
{
    char name[MAX_NAME_LENGTH];
    char symbol;
    int score;
    bool newPlayer;
} Player;

typedef struct
{
    char playerSymbol;
    char oldValue;
    SmallNumber i;
    SmallNumber j;
} Move;
typedef struct
{
    Move *moves;
    SmallNumber currentMove;
    SmallNumber numMovesPlayed;
} MovesHistory;