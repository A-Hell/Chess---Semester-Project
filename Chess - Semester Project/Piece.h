
// This Class Contains the prototype of Base class : Piece 
// And of its inherited Classes: PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING

/*
* Last Edited: 5/7/26
* Author: Amna Akbar
* Description:
	Implemented isValidMove logic for all derived piece classes
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
public:
	Rook();
	Rook(Color colour);

	char getSymbol() const override;
	bool isValidMove(Position from, Position to, const Board& board) const override;
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
public:
	King();
	King(Color colour);

	char getSymbol() const override;
	bool isValidMove(Position from, Position to, const Board& board) const override;
};
