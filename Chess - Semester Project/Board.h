// This Header file Contains the prototype of the Board class
// It is responsible for managing the chessboard, including the positions of pieces, validating moves.

/*
* Last Edited: 5/2/26
* Author: Armaghan
* Description:
	Created the Board class and its member functions.
	Added and Implemented the following functions:
	- Board() : Initializes the chessboard and sets up pieces.
	- GetPiecePosition(Piece* piece) : Returns the position of a given piece.
	- setPiecePosition(Piece* piece, Position pos) : Sets the position of a given piece on the board.
	- movePiece(Position from, Position to) : Moves a piece from one position to another
	- ~Board() : Cleans up any dynamically allocated memory on game.
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
	void movePiece(Position from, Position to); // Moves a piece from one position to another
	Piece* getPiece(int row, int col) const;// Returns the piece at a specific coordinate (needed Interface)

	~Board(); // Cleans up any dynamically allocated memory on game.
};