#include <stdlib.h>
#include "game_definitions.h"
#include "grid.h"
#include "game_logic.h"
#include <unistd.h>

char chooseOpenedSide(SmallNumber i, SmallNumber j, Grid *gameGrid)
{
    SmallNumber row, column;
    SmallNumber directionalArr[2][4] = {
        {0, 0, 1,- 1},
        {1, -1, 0, 0}};

    for (int k = 0; k < 4; k++)
    {
        row = i + directionalArr[0][k];
        column = j + directionalArr[1][k];
        if ((gameGrid->grid[row][column] != PLAYER1) && (gameGrid->grid[row][column] != PLAYER2))
            return gameGrid->grid[row][column];
    }
}

void computerTurn(Grid *gameGrid, char playerSymbol, GameState *currentGame, MovesHistory *movesHistory)
{
    for (int i = 1; i < gameGrid->size; i+=2)
        for (int j = 1; j < gameGrid->size; j += 2)
            if(countBoxSides(i,j,gameGrid) == 3)
            {
                updateGridWithUserInput(gameGrid, playerSymbol, currentGame, chooseOpenedSide(i, j, gameGrid), movesHistory);
                return;
            }
    for (int k = 0; k < 3; k++)
        for (int i = 1; i < gameGrid->size; i += 2)
            for (int j = 1; j < gameGrid->size; j += 2)
                if (countBoxSides(i, j, gameGrid) == k)
                {
                    updateGridWithUserInput(gameGrid, playerSymbol, currentGame, chooseOpenedSide(i, j, gameGrid), movesHistory);
                    return;
                }
}

void turns(Player *player1, Player *player2, Grid *gameGrid, GameState *currentGame, int remainingLines, MovesHistory *movesHistory)
{
    currentGame->CurrentTurn = enPLAYER_1;

    printGrid((*gameGrid), currentGame);
    while (remainingLines >= 0)
    {
        switch (currentGame->CurrentTurn)
        {
        case enPLAYER_1:
            handleUserInput(gameGrid, player1->symbol, currentGame, movesHistory);
            printGrid((*gameGrid), currentGame);
            break;
        case enPLAYER_2:

            if (!(currentGame->versusComputer))
                handleUserInput(gameGrid, player2->symbol, currentGame, movesHistory);
            else
            {
                sleep(1);
                computerTurn(gameGrid, player2->symbol, currentGame, movesHistory);
            }
            printGrid((*gameGrid), currentGame);
            break;
        }

        remainingLines--;
    }
}

int main()
{
    Player player1, player2;
    player1.symbol = PLAYER1;
    player2.symbol = PLAYER2;

    // scanf("%s", player.name);
    // player = findPlayer(player.name);
    // printf("Player: %s\nScore: %d", player.name, player.score);
    // if (player.newPlayer == true)
    // addPlayerToScoreboard(&player);
    // leaderboard(printTop10);

    unsigned char size = 4;
    Grid gameGrid = createGrid(2 * size - 1);
    initializeGrid(&gameGrid);
    GameState currentGame;
    currentGame.versusComputer =true;
    currentGame.player1Score = 0;
    currentGame.player2Score = 0;
    currentGame.remainingLines = (2 * size) * (size - 1);
    currentGame.remainingBoxes = (size - 1) * (size - 1);

    MovesHistory movesHistory;
    movesHistory.moves = (Move *)malloc(sizeof(Move) * (2 * size) * (size - 1));
    movesHistory.currentMove = 0;
    movesHistory.numMovesPlayed = 0;

    turns(&player1, &player2, &gameGrid, &currentGame, currentGame.remainingLines - 1, (&movesHistory));

    freeGrid(&gameGrid);
    return 0;
}
