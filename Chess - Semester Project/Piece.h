
// This Class Contains the prototype of Base class : Piece 
// And of its inherited Classes: PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING

/*
* Last Edited: 5/7/26
* Author: Amna 
* Description:
*- Added: hasMoved boolean flag to Piece base class to track movement history.
* - Added: getMovedStatus() and setMovedStatus() for King and Rook classes.
* - Modified: King::isValidMove to include multi-step validation for Castling (Path check, Attack check, and Initial State check).
*/

#pragma once
#include "Common.h"
class Board;

class Piece
{
protected:
	Color colour;        // Stores the side (WHITE, BLACK, or NONE)
	PieceType piece;     // Stores the type (PAWN, ROOK, etc.)

public:
	// Constructors
	Piece();
	Piece(Color colour, PieceType piece);

	// Virtual Functions (Polymorphism)
	virtual char getSymbol() const = 0;   // Pure virtual: forces subclasses to return 'P', 'R', etc.
	virtual bool isValidMove(Position from, Position to, const Board& board) const = 0;     // Pure virtual: forces subclasses to implement move logic

	// Getters
	Color getColor() const;
	PieceType getType() const;

	virtual ~Piece(); //Virtual destructor for safe memory cleanup
};
// --- Derived Piece Classes ---
class Pawn : public Piece
{
	bool firstMove = true; // Flag to track if the pawn has moved before
public:
	Pawn();
	Pawn(Color colour);

	char getSymbol() const override;
	bool isValidMove(Position from, Position to, const Board& board) const override;
};

class Rook : public Piece
{
private: 
	bool hasMoved;      // Tracks whether the rook has moved before, required for castling validation
public:
	Rook();
	Rook(Color colour);

	char getSymbol() const override;
	bool isValidMove(Position from, Position to, const Board& board) const override;

	// Movement tracking functions
	bool getMovedStatus() const;    // Returns whether the rook has moved at least once during the game
	void setMovedStatus(bool status);  // Updates the rook movement status after a successful move
};

class Knight : public Piece
{
public:
	Knight();
	Knight(Color colour);

	char getSymbol() const override;
	bool isValidMove(Position from, Position to, const Board& board) const override;
};

class Bishop : public Piece
{
public:
	Bishop();
	Bishop(Color colour);

	char getSymbol() const override;
	bool isValidMove(Position from, Position to, const Board& board) const override;
};

class Queen : public Piece
{
public:
	Queen();
	Queen(Color colour);

	char getSymbol() const override;
	bool isValidMove(Position from, Position to, const Board& board) const override;
};

class King : public Piece
{
private:
	bool hasMoved;       // Tracks whether the rook has moved before, required for castling validation
public:
	King();
	King(Color colour);

	char getSymbol() const override;
	bool isValidMove(Position from, Position to, const Board& board) const override;

	// Movement tracking functions
	bool getMovedStatus() const;   // Returns whether the king has moved at least once during the game
	void setMovedStatus(bool status);  // Updates the king movement status after a successful move
};
