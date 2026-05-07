// This Header file Contains the prototype of the Board class
// It is responsible for managing the chessboard, including the positions of pieces, validating moves.

/*
* Last Edited: 5/7/26
* Author: Armaghan
* Description:
*	modified getPiece to take a Position struct instead of separate row and column parameters, to make it consistent with the rest of the codebase
*/


#pragma once
#include "Common.h"
#include "Piece.h"

class Board
{
	Piece* squares[8][8];
public:
	Board(); // Initializes the chessboard and sets up pieces.

	Position GetPiecePosition(Piece* piece) const; // Returns the position of a given piece.
	void setPiecePosition(Piece* piece, Position pos); // Sets the position of a given piece on the board.
	bool movePiece(Position from, Position to); // Moves a piece from one position to another
	Piece* getPiece(Position at) const;// Returns the piece at a specific coordinate (needed Interface)

	~Board(); // Cleans up any dynamically allocated memory on game.
};