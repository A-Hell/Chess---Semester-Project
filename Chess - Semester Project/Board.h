// This Header file Contains the prototype of the Board class
// It is responsible for managing the chessboard, including the positions of pieces, validating moves.

/*
* Last Edited: 5/9/26
* Author: Armaghan
* Description:
*		Removed: Default Parameters from movePiece to force correction function calls
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
	Position moveHistory[100][2]; // stores the history of moves in a 2D array
	string boardHistory[100]; // stores the board state after each move in FEN notation for Three fold repetition rule
	Position lastMoveFrom;   // Add Last Move Tracking
	Position lastMoveTo;
	Piece* lastMovedPiece;
	int lastCapture; // numbers of moves since last capture - used for 50 move rule
	int lastPawnMove; // number of moves since last pawn move - used for 50 move rule
public:
	Board(); // Initializes the chessboard and sets up pieces.

	Position GetPiecePosition(Piece* piece) const; // Returns the position of a given piece.
	void setPiecePosition(Piece* piece, Position pos); // Sets the position of a given piece on the board.
	void setupCastlingTest();
	void promotePawn(Position position, PieceType promotionType);
	bool movePiece(Position from, Position to, bool activeGUI, bool ghost ); // Moves a piece from one position to another
	bool isUnderAttack(Position pos, Color byColor) const; // Checks if a given position is under attack by any pieces of the specified color.
	bool computeCheck(Color on) const; // Checks if the king of the specified color is in check.
	bool lookForMoves(Color on); // Check if the player has any valid moves left
	Piece* getPiece(Position at) const;// Returns the piece at a specific coordinate (needed Interface)
	void storeMoveHistory(Position from, Position to); // Function to store the history of moves 
	void storeBoardHistory(); // Function to store the history of board states in FEN notation for three fold repetition rule
	string toFEN() const; // Converts the current board state to FEN notation
	bool fiftyMoveRule() const; // Check if its been 50 moves without capture or not
	bool threeFoldRepetition() const; // Check if the current board state has occurred 3 times in the history
	Position (*getMoveHistory())[2]; // Returns a pointer to the 2D move history array
	string* getBoardHistory(); // Returns the board state in FEN notation 

	//getters for last move tracking
	Position getLastMoveFrom() const;
	Position getLastMoveTo() const;
	Piece* getLastMovedPiece() const;

	~Board(); // Cleans up any dynamically allocated memory on game.
};