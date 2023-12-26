#include "game_definitions.h"
#include <stdlib.h>

void undo()
{
    //! when a players undoes a move
    // TODO:  decrement currentMove
    // TODO:  and edit the grid to undo this move
}

void undoLine()
{
    // TODO: simply undoes a line by replacing the new value with the old value
}

void undoBox()
{
    // TODO: You can use the function countBoxSides()
    // TODO: and you may edit the function checkAndMarkClosedBox() to take a function pointer to close/open a box
}

void undoGameState()
{
    // TODO: this function should be used to edit any variables in the GameState struct
}

redo()
{
    // TODO: this function performs the next move of the index 'currentMove'
    // TODO: check if currentMove < numMovesPlayed  
}


turn(MovesHistory movesHistory)
{
    Move player1Move;
    Move player2Move;

    // TODO: when a player makes a move add it to this array
    // TODO: and increment the numMovesPlayed
    movesHistory.moves[movesHistory.numMovesPlayed + 1] = player1Move;
    movesHistory.moves[movesHistory.numMovesPlayed + 1] = player2Move;
    movesHistory.numMovesPlayed++;
    movesHistory.currentMove++;
}
int main____fake()
{
    SmallNumber sizeOfGrid = 3;
    MovesHistory movesHistory;
    movesHistory.moves = malloc(sizeof(Move) * (2 * sizeOfGrid) * (sizeOfGrid - 1));
    movesHistory.currentMove = 0;
    movesHistory.numMovesPlayed = 0;
}

