#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "game_definitions.h"
#include "grid.h"
#include "ansi_colors.h"

    //* Dealing with files
Player findPlayer(char *playerName)
{
    FILE *ptrFile = fopen(SCOREBOARD_FILE, "r");
    Player player;
    if (ptrFile != NULL)
    {

        for (int i = 0; i < strlen(playerName); i++)
            playerName[i] = tolower(playerName[i]);

        while (fscanf(ptrFile, "Player: %s\tScore: %d\n", player.name, &player.score) == 2)
        {
            if (strcmp(player.name, playerName) == 0)
            {
                player.newPlayer = false;
                return player;
            }
        }

        //* If player not found, create a new player
        strcpy(player.name, playerName);
        player.newPlayer = true;
        player.score = 0;
        return player;

        fclose(ptrFile);
    }
    else
    {
        printf("Error: Unable to open the scoreboard file in reading mode.\n");
        strcpy(player.name, playerName);
        player.newPlayer = true;
        player.score = 0;
        return player;
    }
}
void addPlayerToScoreboard(Player *player)
{
    FILE *ptrFile = fopen(SCOREBOARD_FILE, "a");
    if (ptrFile != NULL)
        fprintf(ptrFile, "Player: %s\tScore: %d\n", player->name, player->score);
    else
        printf("Error: Unable to open the scoreboard file in append mode.\n");
}
short loadPlayersFromFile(Player **players)
{
    FILE *ptrFile = fopen(SCOREBOARD_FILE, "r");
    if (ptrFile == NULL)
    {
        printf("Error: Unable to open the scoreboard file in reading mode.\n");
        exit(1);
    }

    short capacity = 10;
    *players = (Player *)malloc(capacity * sizeof(Player));
    if (*players == NULL)
    {
        printf("Error: Memory allocation failed.\n");
        fclose(ptrFile);
        exit(1);
    }

    short playersCount = 0;
    while (fscanf(ptrFile, "Player: %s\tScore: %d\n", (*players)[playersCount].name, &(*players)[playersCount].score) == 2)
    {
        playersCount++;
        if (playersCount == capacity)
        {
            capacity *= 2;
            *players = (Player *)realloc(*players, capacity * sizeof(Player));
            if (*players == NULL)
            {
                printf("Error: Memory reallocation failed.\n");
                free(*players);
                fclose(ptrFile);
                exit(1);
            }
        }
    }
    fclose(ptrFile);
    return playersCount;
}

//* Printing titles
void printLeaderboardTitle()
{
    clearConsole();
    printf(BHYEL " __        ________   ______   _______   ________  _______   _______    ______    ______   _______   _______  \n");
    printf("|  \\      |        \\ /      \\ |       \\ |        \\|       \\ |       \\  /      \\  /      \\ |       \\ |       \\ \n");
    printf("| $$      | $$$$$$$$|  $$$$$$\\| $$$$$$$\\| $$$$$$$$| $$$$$$$\\| $$$$$$$\\|  $$$$$$\\|  $$$$$$\\| $$$$$$$\\| $$$$$$$\\ \n");
    printf("| $$      | $$__    | $$__| $$| $$  | $$| $$__    | $$__| $$| $$__/ $$| $$  | $$| $$__| $$| $$  | $$| $$  | $$\n");
    printf("| $$      | $$  \\   | $$    $$| $$  | $$| $$  \\   | $$    $$| $$    $$| $$  | $$| $$    $$| $$  | $$| $$  | $$\n");
    printf("| $$      | $$$$$   | $$$$$$$$| $$  | $$| $$$$$   | $$$$$$$\\| $$$$$$$\\| $$  | $$| $$$$$$$$| $$$$$$$\\| $$  | $$\n");
    printf("| $$_____ | $$_____ | $$  | $$| $$__/ $$| $$_____ | $$  | $$| $$__/ $$| $$__/ $$| $$  | $$| $$  | $$| $$__/ $$\n");
    printf("| $$     \\| $$     \\| $$  | $$| $$    $$| $$     \\| $$  | $$| $$    $$ \\$$    $$| $$  | $$| $$  | $$| $$    $$\n");
    printf(" \\$$$$$$$$ \\$$$$$$$$ \\$$   \\$$ \\$$$$$$$  \\$$$$$$$$ \\$$   \\$$ \\$$$$$$$   \\$$$$$$  \\$$   \\$$ \\$$   \\$$ \\$$$$$$$\n" RESET);
}
void printTop10Title()
{
    clearConsole();

    printf(BHYEL "\t\t\t ________   ______   _______           __    ______  \n");
    printf("\t\t\t|        \\ /      \\ |       \\        _/  \\  /      \\ \n");
    printf("\t\t\t \\$$$$$$$$|  $$$$$$\\| $$$$$$$\\      |   $$ |  $$$$$$\\\n");
    printf("\t\t\t   | $$   | $$  | $$| $$__/ $$       \\$$$$ | $$$\\| $$\n");
    printf("\t\t\t   | $$   | $$  | $$| $$    $$        | $$ | $$$$\\ $$\n");
    printf("\t\t\t   | $$   | $$  | $$| $$$$$$$         | $$ | $$\\$$\\$$\n");
    printf("\t\t\t   | $$   | $$__/ $$| $$             _| $$_| $$_\\$$$$\n");
    printf("\t\t\t   | $$    \\$$    $$| $$            |   $$ \\\\$$  \\$$$\n");
    printf("\t\t\t    \\$$     \\$$$$$$  \\$$             \\$$$$$$ \\$$$$$$ \n" RESET);
}

//* Printing players
void printFirstThreePlayers(Player *players)
{
    printf("\t\t\t\t  |" BHYEL "FIRST: %-14s " RESET "|" BHYEL " %5d " RESET "|\n", players[0].name, players[1].score);
    printf("\t\t\t\t  |" BHYEL "SECOND: %-13s " RESET "|" BHYEL " %5d " RESET "|\n", players[1].name, players[3].score);
    printf("\t\t\t\t  |" BHYEL "THIRD: %-14s " RESET "|" BHYEL " %5d " RESET "|\n", players[2].name, players[3].score);
}
void printPlayers(Player *players, short playersCount)
{
    printf("\t\t\t\t  +----------------------+-------+\n");
    printf("\t\t\t\t  |" BHCYN " Player" RESET "               |" BHRED " Score " RESET "|\n");
    printf("\t\t\t\t  +----------------------+-------+\n");
    printFirstThreePlayers(players);
    for (int i = 3; i < playersCount; i++)
    {
        printf("\t\t\t\t  |" HCYN " %-20s " RESET "|" HRED " %5d " RESET "|\n", players[i].name, players[i].score);
    }
    printf("\t\t\t\t  +----------------------+-------+\n");
}

void printLeaderboard(Player *players, short playersCount)
{
    printLeaderboardTitle();
    printPlayers(players, playersCount);
}
void printTop10(Player *players, short playersCount)
{
    printTop10Title();
    if (playersCount <= 10)
        printPlayers(players, playersCount);
    else
        printPlayers(players, 10);
}

int scoreComparator(const void *x, const void *y)
{
    Player *player1 = (Player *)x;
    Player *player2 = (Player *)y;

    return -1 * ((player1->score) - (player2->score));
}
void leaderboard(void (*whatToPrint)(Player *, short))
{
    Player *players;
    short playersCount = loadPlayersFromFile(&players);
    qsort(players, playersCount, sizeof(Player), scoreComparator);

    if (whatToPrint == &printTop10)
        printTop10(players, playersCount);
    else if (whatToPrint == &printLeaderboard)
        printLeaderboard(players, playersCount);

    free(players); // Free dynamically allocated memory
}

int main()
{
    Player player;
    // scanf("%s", player.name);
    // player = findPlayer(player.name);
    // printf("Player: %s\nScore: %d", player.name, player.score);
    // if (player.newPlayer == true)
    // addPlayerToScoreboard(&player);
    // leaderboard();

    unsigned char size = 3;
    Grid gameGrid = createGrid(2 * size - 1);
    initializeGrid(&gameGrid);
    gameState currentGame;
    currentGame.scoreOfPlayer1 = 0;
    currentGame.scoreOfPlayer2 = 0;
    currentGame.remainingLines = (2 * size) * (size - 1);
    currentGame.remainingBoxes = (size - 1) * (size - 1);

    gameTurn dataOfTurns[currentGame.remainingLines];
    gameTurn *ptrTurn = dataOfTurns;

    turns(&gameGrid, &currentGame, currentGame.remainingLines - 1, ptrTurn);
    printf("check of undo and redo\n");

    undo(ptrTurn, &gameGrid, &currentGame);
    undo(ptrTurn, &gameGrid, &currentGame);
    undo(ptrTurn, &gameGrid, &currentGame);
    undo(ptrTurn, &gameGrid, &currentGame);

    printGrid(gameGrid, &currentGame);

    printf("%c\n", ptrTurn->chosen);
    printf("%d\n", ptrTurn->i);
    printf("%d\n", ptrTurn->j);
    ptrTurn--;
    printf("%c\n", ptrTurn->chosen);
    printf("%d\n", ptrTurn->i);
    printf("%d\n", ptrTurn->j);

    freeGrid(&gameGrid);

    return 0;
}