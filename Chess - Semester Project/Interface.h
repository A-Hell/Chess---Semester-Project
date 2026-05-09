// This Header file contains the prototype of the Interface class
// which will be used to create the User Interface of the Chess Game.

/*
* Last Edited: 5/7/26
* Author: Rayyan
* Description:
	- Added: renderMoveHistory to render last 5 moves
 */

#pragma once
#include "Common.h"
#include "Board.h"

static class Interface
{
public:
    static void renderHeader();

    static void renderBoard(const Board& board, bool isCheck = false); // Prints the board to the console

    static void getMoveInput(Position& from, Position& to); // captures user coordinates
    static bool isValidInput(int row, int col);  // Ensures the user doesn't enter coordinates outside 0-7

    static void renderCurrentPlayer(Color currentPlayer); // Displays which player's turn it is

    static void renderCheckAlert(bool inCheck); // Displays a check alert if the current player is in check

	static void renderMoveHistory(const Position moveHistory[100][2]); // Displays the history of moves made in the game

	static PieceType getPromotionInput(); // Captures user input for pawn promotion
};