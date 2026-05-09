// This Header file Contains the prototype of the Board class
// It is responsible for managing the chessboard, including the positions of pieces, validating moves.

/*
* Last Edited: 5/8/26
* Author: Amna
* Description:
*		Added: LastCapture to keep track of when the last piece was caputre
*		Added: fifity move rule logic which uses lastCapture to check for fiftyMoveRule
*/


#pragma once
#include "Common.h"
#include "Piece.h"

class Board
{
	Piece* squares[8][8]; // 2D array representing the chessboard, where each element is a pointer to a Piece object or nullptr if the square is empty.
	Piece* activePieceWhite[16]; // Array of pointers to active pieces for White.
	Piece* activePieceBlack[16]; // Array of pointers to active pieces for Black.
	Piece* whiteKing;
	Piece* blackKing;
	Position lastMoveFrom;   // Add Last Move Tracking
	Position lastMoveTo;
	Piece* lastMovedPiece;
	int lastCapture; // numbers of moves since last capture - used for 50 move rule
public:
	Board(); // Initializes the chessboard and sets up pieces.

	Position GetPiecePosition(Piece* piece) const; // Returns the position of a given piece.
	void setPiecePosition(Piece* piece, Position pos); // Sets the position of a given piece on the board.
	void setupCastlingTest();
	void promotePawn(Position position, PieceType promotionType);
	bool movePiece(Position from, Position to, bool ghost = false); // Moves a piece from one position to another
	bool isUnderAttack(Position pos, Color byColor) const; // Checks if a given position is under attack by any pieces of the specified color.
	bool computeCheck(Color on) const; // Checks if the king of the specified color is in check.
	bool lookForMoves(Color on); // Check if the player has any valid moves left
	bool fiftyMoveRule() const; // Check if its been 50 moves without capture or not
	Piece* getPiece(Position at) const;// Returns the piece at a specific coordinate (needed Interface)
	//getters for last move tracking
	Position getLastMoveFrom() const;
	Position getLastMoveTo() const;
	Piece* getLastMovedPiece() const;

	~Board(); // Cleans up any dynamically allocated memory on game.
};