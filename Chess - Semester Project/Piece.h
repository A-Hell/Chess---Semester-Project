
// This Class Contains the prototype of Base class : Piece 
// And of its inherited Classes: PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING

/*
* Last Edited: 5/3/26
* Author: Armagahan
* Description: 
	- Fixed the Circular Dependency between Board and Piece through Forward Declaration of Board class in Piece.h
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
	virtual bool isValidMove(Position from, Position to, const Board& board);     // Placeholder for move logic

	// Getters
	Color getColor() const;        
	PieceType getType() const;

	virtual ~Piece(); //Virtual destructor for safe memory cleanup
};
// --- Derived Piece Classes ---
class Pawn : public Piece
{
public:
	Pawn();
	Pawn(Color colour);

	char getSymbol() const override;
};

class Rook : public Piece
{
public:
	Rook();
	Rook(Color colour);

	char getSymbol() const override;
};

class Knight : public Piece
{
public:
	Knight();
	Knight(Color colour);

	char getSymbol() const override;
};

class Bishop : public Piece
{
public:
	Bishop();
	Bishop(Color colour);

	char getSymbol() const override;
};

class Queen : public Piece
{
public:
	Queen();
	Queen(Color colour);

	char getSymbol() const override;
};

class King : public Piece
{
public:
	King();
	King(Color colour);

	char getSymbol() const override;
};
