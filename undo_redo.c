// #include "game_logic.h"
// #include "undo_redo.h"
// #include <stdio.h>
// #include <stdlib.h>
// #include <stdbool.h>

// void undo(gameTurn *ptrTurn, Grid *gameGrid, GameState *currentGame)
// {
//   gameGrid->grid[ptrTurn->i][ptrTurn->j] = ptrTurn->chosen;
//   currentGame->remainingLines++;
//   if (ptrTurn->i % 2 == 0) //! for horizontal lines
//   {
//     if (ptrTurn->i == 0)
//     {
//       if (gameGrid->grid[(ptrTurn->i) + 1][ptrTurn->j] == ptrTurn->symbol)
//       {
//         currentGame->remainingBoxes++;
//         switch (ptrTurn->symbol)
//         {
//         case PLAYER1:
//           currentGame->player1Score++;
//           break;
//         case PLAYER2:
//           currentGame->player2Score++;
//           break;
//         }
//       }
//       gameGrid->grid[(ptrTurn->i) + 1][ptrTurn->j] = ' ';
//     }
//     else if (ptrTurn->i == gameGrid->size - 1)
//     {
//       if (gameGrid->grid[(ptrTurn->i) - 1][ptrTurn->j] == ptrTurn->symbol)
//       {
//         currentGame->remainingBoxes++;
//         switch (ptrTurn->symbol)
//         {
//         case PLAYER1:
//           currentGame->player1Score--;
//           break;
//         case PLAYER2:
//           currentGame->player2Score--;
//           break;
//         }
//         gameGrid->grid[(ptrTurn->i) - 1][ptrTurn->j] = ' ';
//       }
//     }
//     else
//     {
//       if (gameGrid->grid[(ptrTurn->i) + 1][ptrTurn->j] == ptrTurn->symbol)
//       {
//         currentGame->remainingBoxes++;
//         switch (ptrTurn->symbol)
//         {
//         case PLAYER1:
//           currentGame->player1Score--;
//           break;
//         case PLAYER2:
//           currentGame->player2Score--;
//           break;
//         }
//       }
//       if (gameGrid->grid[(ptrTurn->i) - 1][ptrTurn->j] == ptrTurn->symbol)
//       {
//         currentGame->remainingBoxes++;
//         switch (ptrTurn->symbol)
//         {
//         case PLAYER1:
//           currentGame->player1Score--;
//           break;
//         case PLAYER2:
//           currentGame->player2Score--;
//           break;
//         }
//         gameGrid->grid[(ptrTurn->i) - 1][ptrTurn->j] = ' ';
//       }
//       gameGrid->grid[(ptrTurn->i) - 1][ptrTurn->j] = ' ';
//       gameGrid->grid[(ptrTurn->i) + 1][ptrTurn->j] = ' ';
//     }
//   }

//   else if (ptrTurn->j % 2 == 0) //! for vertival lines
//   {

//     if (ptrTurn->j == 0)
//     {
//       if (gameGrid->grid[ptrTurn->i][(ptrTurn->j)+1] == ptrTurn->symbol)
//       {
//         currentGame->remainingBoxes++;
//         switch (ptrTurn->symbol)
//         {
//         case PLAYER1:
//           currentGame->player1Score--;
//           break;
//         case PLAYER2:
//           currentGame->player2Score--;
//           break;
//         }
//       }
//       gameGrid->grid[ptrTurn->i][(ptrTurn->j) + 1] = ' ';
//     }
//     else if (ptrTurn->j == gameGrid->size - 1)
//     {
//       if (gameGrid->grid[ptrTurn->i][(ptrTurn->j)-1] == ptrTurn->symbol)
//       {
//         currentGame->remainingBoxes++;
//         switch (ptrTurn->symbol)
//         {
//         case PLAYER1:
//           currentGame->player1Score--;
//           break;
//         case PLAYER2:
//           currentGame->player2Score--;
//           break;
//         }
//       }
//       gameGrid->grid[ptrTurn->i][(ptrTurn->j) - 1] = ' ';
//     }
//     else
//     { if (gameGrid->grid[ptrTurn->i][(ptrTurn->j)+1] == ptrTurn->symbol)
//       {
//         currentGame->remainingBoxes++;
//         switch (ptrTurn->symbol)
//         {
//         case PLAYER1:
//           currentGame->player1Score--;
//           break;
//         case PLAYER2:
//           currentGame->player2Score--;
//           break;
//         }
//       }
//       if (gameGrid->grid[ptrTurn->i][(ptrTurn->j)-1] == ptrTurn->symbol)
//       {
//         currentGame->remainingBoxes++;
//         switch (ptrTurn->symbol)
//         {
//         case PLAYER1:
//           currentGame->player1Score--;
//           break;
//         case PLAYER2:
//           currentGame->player2Score--;
//           break;
//         }
//       }
//       gameGrid->grid[ptrTurn->i][(ptrTurn->j) + 1] = ' ';
//       gameGrid->grid[ptrTurn->i][(ptrTurn->j) - 1] = ' ';
//     }
//   }

// }
// void redo (gameTurn *ptrTurn, Grid *gameGrid, GameState *currentGame)
// {
//  ptrTurn++;
//  gameGrid->grid[ptrTurn->i][ptrTurn->j]=PLAYER1;
//  currentGame->remainingLines--;
//  checkBoxesAroundLine(ptrTurn->i,ptrTurn->j,gameGrid,ptrTurn->symbol,currentGame);
// }
// //checkBoxesAroundLine(int i, int j, Grid *gameGrid, char playerSymbol, GameState *currentGame)