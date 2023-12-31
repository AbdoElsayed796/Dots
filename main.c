#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "game_definitions.h"
#include "grid.h"
#include "ansi_colors.h"
#include "scoreboard_manager.h"
#include "user_input.h"
#include "computer_turn.h"
#include "save_load.h"

void pause()
{
    printf("\nPress any key to continue ...\n");
    getchar();
    getchar();
}
void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}
void userManual()
{
    clearConsole();
    printGameTitle();
    printf(BHBLU "\n\n\t\t\t\t\t\t\t\tUser Manual:\n\n" BWHT);
    printf("\t\t\t- The game has four grid sizes from 3x3 to 6x6.\n");
    printf("\t\t\t- There are two modes: multiplayer or single player.\n");
    printf("\t\t\t- Each side is represented by a character, and letters are case sensitive.\n");
    printf("\t\t\t- To perform actions like undo, redo, save, or exit, type the respective word.\n");
    printf(BHRED "\n\t\t\t\t\t\t\t   Enjoy playing the game!\n" RESET);

    pause();
}
void initializeGameGrid(Grid *gameGrid)
{
    do
    {
        clearConsole();
        printGameTitle();
        printf(BWHT "\n\n\t\t\t\t\t\t\tEnter Grid Size (3-6): " RESET);
        scanf("%d", &gameGrid->size);
        clearInputBuffer();
    } while (!(gameGrid->size >= 3 && gameGrid->size <= 6));
    *gameGrid = createGrid(2 * gameGrid->size - 1);
    initializeGrid(gameGrid);
}
void initalizeGameState(GameState *currentGame, SmallNumber gridSize)
{
    int userInput;
    currentGame->player1Score = 0;
    currentGame->player2Score = 0;
    currentGame->remainingLines = (2 * gridSize) * (gridSize - 1);
    currentGame->remainingBoxes = (gridSize - 1) * (gridSize - 1);
    do
    {
        clearConsole();
        printGameTitle();
        printf(BWHT "\n\n\t\t\t\t\t\t\tChoose mode:\n");
        printf("\t\t\t\t\t\t\t1- Against Computer\n");
        printf("\t\t\t\t\t\t\t2- Multiplayer\n");
        printf("\t\t\t\t\t\t\tEnter your choice: " RESET);
        scanf("%d", &userInput);
        clearInputBuffer();

        if (userInput == 1)
            currentGame->versusComputer = true;
        else if (userInput == 2)
        {
            currentGame->versusComputer = false;
        }
        else
        {
            sleep(1);
            printf("Invalid choice! Please enter 1 or 2.\n");
        }
    } while (userInput != 1 && userInput != 2);
}
void printWelcomeMessageAndAddNewPlayers(Player *player)
{
    if (!player->newPlayer)
    {
        printf(BHMAG "\n\t\t\t\t\t\t\t\tWelcome Back! ");
        printf(BHCYN "\n\t\t\t\t\t\t\tIt's very nice to see you again! " RESET);
        sleep(2);
    }
    else
    {
        printf(BHBLU "\n\t\t\t\t\t\t\tWelcome To Our Game! ");
        printf(BHBLU "\n\t\t\t\t\t\t\tI hope you enjoy it :)" RESET);
        sleep(2);
        addPlayerToScoreboard(player);
    }
}
void initializePlayers(Player *player1, Player *player2, bool versusComputer)
{
    clearConsole();
    printGameTitle();
    if (versusComputer)
        printf(BWHT "\n\n\t\t\t\t\t\t\tPlease enter your name: " RESET);
    else
        printf(BWHT "\n\n\t\t\t\t\t\t\tPlease enter your name (Player 1): " RESET);

    scanf("%s", &player1->name);
    *player1 = findPlayer(player1->name);
    player1->symbol = PLAYER1;
    printWelcomeMessageAndAddNewPlayers(player1);

    if (versusComputer)
    {
        player2->score = 0;
        player2->symbol = PLAYER2;
    }
    else
    {
        printf(BWHT "\n\n\t\t\t\t\t\t\tPlease enter your name (Player 2): " RESET);
        scanf("%s", &player2->name);
        *player2 = findPlayer(player2->name);
        player2->symbol = PLAYER2;
        printWelcomeMessageAndAddNewPlayers(player2);
    }
}
void initalizeMovesHistory(MovesHistory *movesHistory, SmallNumber gridSize)
{
    movesHistory->moves = (Move *)malloc(sizeof(Move) * (2 * gridSize) * (gridSize - 1));
    movesHistory->currentMove = 0;
    movesHistory->numMovesPlayed = 0;
}
void startTurns(Player *player1, Player *player2, Grid *gameGrid, GameState *currentGame, MovesHistory *movesHistory)
{
    currentGame->CurrentTurn = enPLAYER_1;

    printGrid((*gameGrid), currentGame);
    while (currentGame->remainingLines > 0)
    {
        switch (currentGame->CurrentTurn)
        {
        case enPLAYER_1:
            handleUserInput(gameGrid, currentGame, movesHistory, player1, player2);
            printGrid((*gameGrid), currentGame);
            break;
        case enPLAYER_2:

            if (!(currentGame->versusComputer))
                handleUserInput(gameGrid, currentGame, movesHistory, player1, player2);
            else
            {
                sleep(1);
                computerTurn(gameGrid, player2->symbol, currentGame, movesHistory);
            }
            printGrid((*gameGrid), currentGame);
            break;
        }
    }
}
void newGame(Grid *gameGrid, GameState *currentGame, MovesHistory *movesHistory, Player *player1, Player *player2)
{
    initializeGameGrid(gameGrid);
    initalizeGameState(currentGame, (gameGrid->size + 1) / 2);
    initializePlayers(player1, player2, currentGame->versusComputer);
    initalizeMovesHistory(movesHistory, gameGrid->size);

    startTurns(player1, player2, gameGrid, currentGame, movesHistory);

    freeGrid(gameGrid);
}

bool loadGame(Grid *gameGrid, GameState *currentGame, MovesHistory *movesHistory, Player *player1, Player *player2)
{
    FILE *filePtr;
    int userInput;
    clearConsole();
    printGameTitle();
    printf(BHWHT "\n\t\t\t\t\t\t\t\tChoose a file:\n\n");
    printf(BHWHT "\t\t\t\t\t\t\t1- %s", openFileAndReadDate(&filePtr, GAME_1));
    fclose(filePtr);
    printf(BHWHT "\n\t\t\t\t\t\t\t2- %s", openFileAndReadDate(&filePtr, GAME_2));
    fclose(filePtr);
    printf(BHWHT "\n\t\t\t\t\t\t\t3- %s\n", openFileAndReadDate(&filePtr, GAME_3));
    fclose(filePtr);
    scanf("%d", &userInput);
    switch (userInput)
    {
    case 1:
        readGame(gameGrid, currentGame, movesHistory, player1, player2, GAME_1);
        break;
    case 2:
        readGame(gameGrid, currentGame, movesHistory, player1, player2, GAME_2);
        break;
    case 3:
        readGame(gameGrid, currentGame, movesHistory, player1, player2, GAME_3);
        break;
    default:
        return false;
    }

    startTurns(player1, player2, gameGrid, currentGame, movesHistory);
    freeGrid(gameGrid);

    return true;
}


UserAction mainMenu(Grid *gameGrid, GameState *currentGame, MovesHistory *movesHistory, Player *player1, Player *player2)
{
    int option;
    printf(BWHT "\n\n\t\t\t\t\t\t\t1- User Manual\n");
    printf("\t\t\t\t\t\t\t2- Leaderboard\n");
    printf("\t\t\t\t\t\t\t3- New Game\n");
    printf("\t\t\t\t\t\t\t4- Load Game\n");
    printf("\t\t\t\t\t\t\t5- Exit\n\t\t\t\t\t\t\t" RESET);
    scanf("%d", &option);
    clearInputBuffer();
    switch (option)
    {
    case 1:
        userManual();
        return enOTHER;
        break;
    case 2:
        clearConsole();
        printf(BWHT "\n1- Top 10");
        printf("\n2- Full Leaderboard\n" RESET);
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            leaderboard(printTop10);
            pause();
            return enOTHER;
            break;
        case 2:
            leaderboard(printLeaderboard);
            pause();
            return enOTHER;
            break;
        }
        break;
    case 3:
        newGame(gameGrid, currentGame, movesHistory, player1, player2);
        return enEXIT;
        break;
    case 4:
        if(loadGame(gameGrid, currentGame, movesHistory, player1, player2))
        {
            return enEXIT;
        }
        return enOTHER;
        break;
    case 5:
        return enEXIT;
        break;
    default:
        printf(BHRED "\t\t\t\t\t\t\t\tInvalid input\n" RESET);
        printf("\n\nPress any key to continue ...\n");
        getchar();
        return enOTHER;
        break;
    }
    return enOTHER;
}

int main()
{
    Grid gameGrid;
    GameState currentGame;
    Player player1, player2;
    MovesHistory movesHistory;

    UserAction userInput;
    do
    {
        clearConsole();
        printGameTitle();
        userInput = mainMenu(&gameGrid, &currentGame, &movesHistory, &player1, &player2);
    } while (userInput != enEXIT);
}