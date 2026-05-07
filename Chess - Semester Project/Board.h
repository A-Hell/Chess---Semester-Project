// This Header file Contains the prototype of the Board class
// It is responsible for managing the chessboard, including the positions of pieces, validating moves.

/*
* Last Edited: 5/7/26
* Author: Armaghan
* Description:
*		Added Logic for Watching Checks on Kings:
*			Added an Array of Pieces of each side to be more efficent when searching for pieces
			Added isUnderAttack function to check if a given square is being attacked by a specific player's piece
			Added computeCheck to check if a player's King is under check or not
*			
*/


#pragma once
#include "Common.h"
#include "Piece.h"

class Board
{
	Piece* squares[8][8]; // 2D array representing the chessboard, where each element is a pointer to a Piece object or nullptr if the square is empty.
	Piece* activePieceWhite[16]; // Array of pointers to active pieces for White.
	Piece* activePieceBlack[16]; // Array of pointers to active pieces for Black.
public:
	Board(); // Initializes the chessboard and sets up pieces.

	Position GetPiecePosition(Piece* piece) const; // Returns the position of a given piece.
	void setPiecePosition(Piece* piece, Position pos); // Sets the position of a given piece on the board.
	bool movePiece(Position from, Position to, bool inCheck = false); // Moves a piece from one position to another
	bool isUnderAttack(Position pos, Color byColor) const; // Checks if a given position is under attack by any pieces of the specified color.
	bool computeCheck(Color on) const; // Checks if the king of the specified color is in check.
	Piece* getPiece(Position at) const;// Returns the piece at a specific coordinate (needed Interface)

	~Board(); // Cleans up any dynamically allocated memory on game.
};