// This Header file contains the prototype of the Interface class
// which will be used to create the User Interface of the Chess Game.

/*
* Last Edited: 5/7/26
* Author: Rayyan
* Description:
    - Added renderBoard to visualize the 8x8 grid.
    - Added getMoveInput to capture 'From' and 'To' coordinates from the console.
    - Added isValidInput for basic 0-7 coordinate validation.
    - Added Function in interface to display current player
*/

#pragma once
#include "Common.h"
#include "Board.h"

class Interface
{
public:
    void renderBoard(const Board& board); // Prints the board to the console

    void getMoveInput(Position& from, Position& to); // captures user coordinates
    
    bool isValidInput(int row, int col);  // Ensures the user doesn't enter coordinates outside 0-7

    void renderCurrentPlayer(Color currentPlayer); // Displays which player's turn it is
};