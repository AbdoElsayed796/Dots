#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "game_definitions.h"
#include "grid.h"
#include "ansi_colors.h"
#include "undo_redo.h"
void undo(Grid *gameGrid, MovesHistory *movesHistory, GameState *currentGame)
{
    undoLine(gameGrid, movesHistory, currentGame);   
}

void undoLine(Grid *gameGrid, MovesHistory *movesHistory, GameState *currentGame)
{
    gameGrid->grid[movesHistory->moves[movesHistory->currentMove].i][movesHistory->moves[movesHistory->currentMove].j] = movesHistory->moves[movesHistory->currentMove].oldValue;
    undoBox(gameGrid, movesHistory, currentGame);
}

void undoBox(Grid *gameGrid, MovesHistory *movesHistory, GameState *currentGame)
{
    int numberOfBoxesOPend = 0;
    char symbol=movesHistory->moves[movesHistory->currentMove].playerSymbol;
    int i= movesHistory->moves[movesHistory->currentMove].i;
    int j= movesHistory->moves[movesHistory->currentMove].j;

    if (i % 2 == 0)
    {
        if (i == 0)
        {  gameGrid->grid[i+1][j]==' ';
          if(countBoxSides(i+1,j,gameGrid)==3)
            { 
                numberOfBoxesOPend++;
            }          
        }
        else if (i == gameGrid->size - 1)
        {    
             gameGrid->grid[i-1][j]==' ';
             if(countBoxSides(i-1,j,gameGrid)==3)
             {  
                numberOfBoxesOPend++;
             }           
        }
        else
        {    
             gameGrid->grid[i+1][j]==' ';
              gameGrid->grid[i-1][j]==' ';
            if(countBoxSides(i+1,j,gameGrid)==3)
            {          
                numberOfBoxesOPend++;
            }    
              if(countBoxSides(i-1,j,gameGrid)==3)
             {   
                numberOfBoxesOPend++;
             }                  
        }          
     }
    
    else if(j % 2 ==0)
    {
      if (j == 0)
        { gameGrid->grid[i][j+1]==' ';
          if(countBoxSides(i,j+1,gameGrid)==3)
            {         
                numberOfBoxesOPend++;
            }    
        }
        else if (j == gameGrid->size - 1)
        {   
             gameGrid->grid[i][j-1]==' ';
        
             if(countBoxSides(i,j-1,gameGrid)==3)
             {             
                numberOfBoxesOPend++;
             }
        }  
        else
        {
              gameGrid->grid[i][j+1]==' ';
              gameGrid->grid[i][j-1]==' ';
            if(countBoxSides(i,j+1,gameGrid)==3)
            {
                numberOfBoxesOPend++;
            }
              if(countBoxSides(i,j-1,gameGrid)==3)
             {                  
                numberOfBoxesOPend++;
             }
             
        }    

}
    
    
undoGameState(movesHistory,currentGame,numberOfBoxesOPend,symbol);
}
void undoGameState(MovesHistory *movesHistory,GameState *currentGame,int numberOfBoxesOPend,char symbol)
{
    movesHistory->numMovesPlayed++;
    currentGame->remainingLines++;
    switch(symbol)
    {
    case PLAYER1:
    currentGame->player1Score-=numberOfBoxesOPend;
        break;
    case PLAYER2:
    currentGame->player2Score-=numberOfBoxesOPend;
    break;
    }
    currentGame->remainingBoxes+=numberOfBoxesOPend;

    movesHistory->currentMove--;
}
void redo(Grid *gameGrid, MovesHistory *movesHistory,GameState *currentGame)
{
    movesHistory->currentMove;
    SmallNumber size =(((gameGrid->size+1)/2));
    size=(2*size)*(size-1);
    if(movesHistory->currentMove<gameGrid->size)
    {
       gameGrid->grid[movesHistory->moves[movesHistory->currentMove].i][movesHistory->moves[movesHistory->currentMove].j] =movesHistory->moves[movesHistory->currentMove].playerSymbol; 
       currentGame->remainingLines--;
       checkBoxesAroundLine(movesHistory->moves[movesHistory->currentMove].i,movesHistory->moves[movesHistory->currentMove].j,gameGrid,movesHistory->moves[movesHistory->currentMove].playerSymbol,currentGame);
    }
    //void checkBoxesAroundLine(int i, int j, Grid *gameGrid, char playerSymbol, GameState *currentGame)
}

// turn(MovesHistory movesHistory)
// {
//     Move player1Move;
//     Move player2Move;

//     // TODO: when a player makes a move add it to this array
//     // TODO: and increment the numMovesPlayed
//     movesHistory.moves[movesHistory.numMovesPlayed + 1] = player1Move;
//     movesHistory.moves[movesHistory.numMovesPlayed + 1] = player2Move;
//     movesHistory.numMovesPlayed++;
//     movesHistory.currentMove++;
// }
// int main____fake()
// {
//     SmallNumber sizeOfGrid = 3;
//     MovesHistory movesHistory;
//     movesHistory.moves = malloc(sizeof(Move) * (2 * sizeOfGrid) * (sizeOfGrid - 1));
//     movesHistory.currentMove = 0;
//     movesHistory.numMovesPlayed = 0;
// }
int main()
{
    Player player;
    // scanf("%s", player.name);
    // player = findPlayer(player.name);
    // printf("Player: %s\nScore: %d", player.name, player.score);
    // if (player.newPlayer == true)
    // addPlayerToScoreboard(&player);
    // leaderboard(printTop10);

    unsigned char size = 3;
    Grid gameGrid = createGrid(2 * size - 1);
    initializeGrid(&gameGrid);
    GameState currentGame;
    currentGame.player1Score = 0;
    currentGame.player2Score = 0;
    currentGame.remainingLines = (2 * size) * (size - 1);
    currentGame.remainingBoxes = (size - 1) * (size - 1);

    MovesHistory movesHistory;
    movesHistory.moves = (Move *)malloc(sizeof(Move) * (2 * size) * (size - 1));
    movesHistory.currentMove = 0;
    movesHistory.numMovesPlayed = 0;

    turns(&gameGrid, &currentGame, currentGame.remainingLines - 1, &movesHistory);

    freeGrid(&gameGrid);
    return 0;
}
