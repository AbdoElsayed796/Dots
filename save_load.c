#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "game_definitions.h"
#include "grid.h"
#include "ansi_colors.h"

char *openFileAndReadDate(FILE **filePtr, char *filename);// declaration

//* Saving Game
void openFileAndWriteDate(FILE **filePtr, char *filename)
{
    *filePtr = fopen(filename, "wb");
    if (filePtr == NULL)
    {
        printf("Failed to open file for writing.\n");
        exit(1);
    }
    else
    {
        time_t now = time(NULL);
        char *formattedTime = ctime(&now);
        fwrite(formattedTime, sizeof(char), FORMATTED_DATE_SIZE, *filePtr);
    }
}
void writeGrid(FILE **filePtr, Grid *gameGrid)
{
    fwrite(&(gameGrid->size), sizeof(SmallNumber), 1, *filePtr);

    for (int i = 0; i < gameGrid->size; i++)
        for (int j = 0; j < gameGrid->size; j++)
            fwrite(&gameGrid->grid[i][j], sizeof(char), 1, *filePtr);
}
void writePlayer(FILE **filePtr, Player *player)
{
    fwrite(player, sizeof(Player), 1, *filePtr);
}
void writeGameState(FILE **filePtr, GameState *currentGame)
{
    fwrite(currentGame, sizeof(GameState), 1, *filePtr);
}
void writeMovesHistory(FILE **filePtr, MovesHistory *movesHistory)
{
    fwrite(&(movesHistory->currentMove), sizeof(SmallNumber), 1, *filePtr);
    fwrite(&(movesHistory->numMovesPlayed), sizeof(SmallNumber), 1, *filePtr);
    fwrite(movesHistory->moves, sizeof(Move), movesHistory->numMovesPlayed + 1, *filePtr);
}
void saveGameData(Grid *gameGrid, GameState *currentGame, MovesHistory *movesHistory, Player *player1, Player *player2, char *filename)
{
    FILE *filePtr;
    openFileAndWriteDate(&filePtr, filename);
    writeGrid(&filePtr, gameGrid);
    writePlayer(&filePtr, player1);
    writeGameState(&filePtr, currentGame);
    writeMovesHistory(&filePtr, movesHistory);
    fclose(filePtr);
}
bool saveGame(Grid *gameGrid, GameState *currentGame, MovesHistory *movesHistory, Player *player1, Player *player2)//* returns true if successful
{
    FILE *filePtr;
    int userInput;
    printf(BHWHT "\n\n\t\t\t\t\t\tChoose a file:\n\n");
    printf(BHWHT "\t\t\t\t\t1- %s", openFileAndReadDate(&filePtr, GAME_1));
    fclose(filePtr);
    printf(BHWHT "\n\t\t\t\t\t2- %s", openFileAndReadDate(&filePtr, GAME_2));
    fclose(filePtr);
    printf(BHWHT "\n\t\t\t\t\t3- %s\n", openFileAndReadDate(&filePtr, GAME_3));
    fclose(filePtr);
    scanf("%d", &userInput);
    switch (userInput)
    {
    case 1:
        saveGameData(gameGrid, currentGame, movesHistory, player1, player2, GAME_1);
        break;
    case 2:
        saveGameData(gameGrid, currentGame, movesHistory, player1, player2, GAME_2);
        break;
    case 3:
        saveGameData(gameGrid, currentGame, movesHistory, player1, player2, GAME_3);
        break;
    default:
        return false;
    }

    return true;
}

//* Reading Game
char *openFileAndReadDate(FILE **filePtr, char *filename)
{
    *filePtr = fopen(filename, "rb");
    if (filePtr == NULL)
    {
        printf("Failed to open file for reading.\n");
        exit(1);
    }
    else
    {
        char *formattedTime = (char *)malloc(sizeof(char) * FORMATTED_DATE_SIZE);
        fread(formattedTime, sizeof(char), FORMATTED_DATE_SIZE, *filePtr);
        return formattedTime;
    }
}
void readGrid(FILE **filePtr, Grid *gameGrid)
{
    fread(&(gameGrid->size), sizeof(char), 1, *filePtr);
    *gameGrid = createGrid(gameGrid->size);
    for (int i = 0; i < gameGrid->size; i++)
        for (int j = 0; j < gameGrid->size; j++)
            fread(&gameGrid->grid[i][j], sizeof(char), 1, *filePtr);
}
void readPlayer(FILE **filePtr, Player *player)
{
    fread(player, sizeof(Player), 1, *filePtr);
}
void readGameState(FILE **filePtr, GameState *currentGame)
{
    fread(currentGame, sizeof(GameState), 1, *filePtr);
}
void readMovesHistory(FILE **filePtr, MovesHistory *movesHistory, SmallNumber gridSize)
{
    fread(&(movesHistory->currentMove), sizeof(SmallNumber), 1, *filePtr);
    fread(&(movesHistory->numMovesPlayed), sizeof(SmallNumber), 1, *filePtr);

    movesHistory->moves = (Move *)malloc(sizeof(Move) * (2 * gridSize) * (gridSize - 1));
    fread(movesHistory->moves, sizeof(Move), movesHistory->numMovesPlayed + 1, *filePtr);
}
void readGame(Grid *gameGrid, GameState *currentGame, MovesHistory *movesHistory, Player *player1, Player *player2, char *filename)
{
    FILE *filePtr;
    openFileAndReadDate(&filePtr, filename);
    readGrid(&filePtr, gameGrid);
    readPlayer(&filePtr, player1);
    readGameState(&filePtr, currentGame);
    readMovesHistory(&filePtr, movesHistory, gameGrid->size);
    printGrid(*gameGrid, currentGame);
    fclose(filePtr);
}
