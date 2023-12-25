#pragma once
#include "game_logic.h"

void undo(gameTurn *ptrTurn, Grid *gameGrid, gameState *currentGame)
{
  gameGrid->grid[ptrTurn->i][ptrTurn->j] = ptrTurn->chosen;
  currentGame->remainingLines--;
  if (ptrTurn->i % 2 == 0) //! for horizontal lines
  {
    if (ptrTurn->i == 0)
    {
      if (gameGrid->grid[(ptrTurn->i) + 1][ptrTurn->j] == ptrTurn->symbol)
      {
        currentGame->remainingBoxes--;
        switch (ptrTurn->symbol)
        {
        case PLAYER1:
          currentGame->scoreOfPlayer1--;
          break;
        case PLAYER2:
          currentGame->scoreOfPlayer2--;
          break;
        }
      }
      gameGrid->grid[(ptrTurn->i) + 1][ptrTurn->j] = ' ';
    }
    else if (ptrTurn->i == gameGrid->size - 1)
    {
      if (gameGrid->grid[(ptrTurn->i) - 1][ptrTurn->j] == ptrTurn->symbol)
      {
        currentGame->remainingBoxes--;
        switch (ptrTurn->symbol)
        {
        case PLAYER1:
          currentGame->scoreOfPlayer1--;
          break;
        case PLAYER2:
          currentGame->scoreOfPlayer2--;
          break;
        }
        gameGrid->grid[(ptrTurn->i) - 1][ptrTurn->j] = ' ';
      }
    }
    else
    {
      if (gameGrid->grid[(ptrTurn->i) + 1][ptrTurn->j] == ptrTurn->symbol)
      {
        currentGame->remainingBoxes--;
        switch (ptrTurn->symbol)
        {
        case PLAYER1:
          currentGame->scoreOfPlayer1--;
          break;
        case PLAYER2:
          currentGame->scoreOfPlayer2--;
          break;
        }
      }
      if (gameGrid->grid[(ptrTurn->i) - 1][ptrTurn->j] == ptrTurn->symbol)
      {
        currentGame->remainingBoxes--;
        switch (ptrTurn->symbol)
        {
        case PLAYER1:
          currentGame->scoreOfPlayer1--;
          break;
        case PLAYER2:
          currentGame->scoreOfPlayer2--;
          break;
        }
        gameGrid->grid[(ptrTurn->i) - 1][ptrTurn->j] = ' ';
      }
      gameGrid->grid[(ptrTurn->i) - 1][ptrTurn->j] = ' ';
      gameGrid->grid[(ptrTurn->i) + 1][ptrTurn->j] = ' ';
    }
  }

  else if (ptrTurn->j % 2 == 0) //! for vertival lines
  {

    if (ptrTurn->j == 0)
    {
      if (gameGrid->grid[ptrTurn->i][(ptrTurn->j)+1] == ptrTurn->symbol)
      {
        currentGame->remainingBoxes--;
        switch (ptrTurn->symbol)
        {
        case PLAYER1:
          currentGame->scoreOfPlayer1--;
          break;
        case PLAYER2:
          currentGame->scoreOfPlayer2--;
          break;
        }
      }
      gameGrid->grid[ptrTurn->i][(ptrTurn->j) + 1] = ' ';
    }
    else if (ptrTurn->j == gameGrid->size - 1)
    {
      if (gameGrid->grid[ptrTurn->i][(ptrTurn->j)-1] == ptrTurn->symbol)
      {
        currentGame->remainingBoxes--;
        switch (ptrTurn->symbol)
        {
        case PLAYER1:
          currentGame->scoreOfPlayer1--;
          break;
        case PLAYER2:
          currentGame->scoreOfPlayer2--;
          break;
        }
      }
      gameGrid->grid[ptrTurn->i][(ptrTurn->j) - 1] = ' ';
    }
    else
    { if (gameGrid->grid[ptrTurn->i][(ptrTurn->j)+1] == ptrTurn->symbol)
      {
        currentGame->remainingBoxes--;
        switch (ptrTurn->symbol)
        {
        case PLAYER1:
          currentGame->scoreOfPlayer1--;
          break;
        case PLAYER2:
          currentGame->scoreOfPlayer2--;
          break;
        }
      }
      if (gameGrid->grid[ptrTurn->i][(ptrTurn->j)-1] == ptrTurn->symbol)
      {
        currentGame->remainingBoxes--;
        switch (ptrTurn->symbol)
        {
        case PLAYER1:
          currentGame->scoreOfPlayer1--;
          break;
        case PLAYER2:
          currentGame->scoreOfPlayer2--;
          break;
        }
      }
      gameGrid->grid[ptrTurn->i][(ptrTurn->j) + 1] = ' ';
      gameGrid->grid[ptrTurn->i][(ptrTurn->j) - 1] = ' ';
    }
  }
}