// This Header file contains the prototype of the Interface class
// which will be used to create the User Interface of the Chess Game.

/*
* Last Edited: 5/7/26
* Author: Rayyan
* Description:
    - Added: renderCheckAlert to display a check alert if the current player is in check.
    - Added: renderHeader to display a header at the start of the game
*/

#pragma once
#include "Common.h"
#include "Board.h"

class Interface
{
public:
    void renderHeader();

    void renderBoard(const Board& board, bool isCheck = false); // Prints the board to the console

    void getMoveInput(Position& from, Position& to); // captures user coordinates

    bool isValidInput(int row, int col);  // Ensures the user doesn't enter coordinates outside 0-7

    void renderCurrentPlayer(Color currentPlayer); // Displays which player's turn it is

    void renderCheckAlert(bool inCheck); // Displays a check alert if the current player is in check
};