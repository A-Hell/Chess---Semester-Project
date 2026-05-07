/*
* Last Edited: 5/7/26
* Author: Armaghan
* Description:
		Implemented: isUnderAttack, Function looks through the array of specified color and calls isValidMove on each active to see if it can reach the specified sqaure
		Implemented: computeCheck, Function calls isUnderAttack on the coordinates of the King of a specific color to see if it is in danger or not
		Modified:	Constructor to insure correct standard assigning of ActivePieces
		Modified:	movePiece to cater to the activePiece array and ensure proper dynamic memory handeling
					added Logic to compute checks after each move and to block and reverse a move that leads to check
*/

#include "Board.h"


// Default Constructor
Board::Board()
{
	// Set the board on default Settings
	
	// Set Up Black
	squares[0][0] = new Rook(BLACK);
	squares[0][1] = new Knight(BLACK);
	squares[0][2] = new Bishop(BLACK);
	squares[0][3] = new Queen(BLACK);
	squares[0][4] = new King(BLACK);
	squares[0][5] = new Bishop(BLACK);
	squares[0][6] = new Knight(BLACK);
	squares[0][7] = new Rook(BLACK);
	for (int i = 0; i < 8; i++)
	squares[1][i] = new Pawn(BLACK);

	// Set Up White
	squares[7][0] = new Rook(WHITE);
	squares[7][1] = new Knight(WHITE);
	squares[7][2] = new Bishop(WHITE);
	squares[7][3] = new Queen(WHITE);
	squares[7][4] = new King(WHITE);
	squares[7][5] = new Bishop(WHITE);
	squares[7][6] = new Knight(WHITE);
	squares[7][7] = new Rook(WHITE);
	for (int i = 0; i < 8; i++)
	squares[6][i] = new Pawn(WHITE);

	// Assign Active Pieces
	for (int i = 0; i < 8; i++)
	{
		// First 8 are the main pieces, next 8 are the pawns
		activePieceBlack[i] = squares[0][i];
		activePieceBlack[i+8] = squares[1][i];

		activePieceWhite[i] = squares[7][i];
		activePieceWhite[i+8] = squares[6][i];
	}

	// Set the Rest of the board as Empty
	for (int i = 2; i < 6; i++)
		for (int j = 0; j < 8; j++)
			squares[i][j] = nullptr;

}

Position Board::GetPiecePosition(Piece* piece) const
{
	for (int i = 0; i < 8; i++)
		for (int j = 0;j < 8; j++)
			if (squares[i][j] == piece)
				return { i,j };
	return { -1,-1 };
}

void Board::setPiecePosition(Piece* piece, Position pos)
{
	// Block Invalid Indexes and Null Piece
	if (pos.row < 0 || pos.row > 7 || pos.col < 0 || pos.col > 8 || !piece)
		return;

	squares[pos.row][pos.col] = piece;
}

bool Board::movePiece(Position from, Position to, bool inCheck)
{
	// Block Invalid Indexes
	if (from.row < 0 || from.row > 7 || from.col < 0 || from.col > 7 ||
		to.row < 0 || to.row > 7 || to.col < 0 || to.col > 7)
		return false;
	// Block Null Piece
	if (!squares[from.row][from.col])
		return false;

	Piece* toMove = squares[from.row][from.col];
	
	// Block Invalid Piece Behaviour
	if (!toMove->isValidMove(from, to, *this))
		return false;

	// Block Taking Own Piece
	if (squares[to.row][to.col] && squares[to.row][to.col]->getColor() == toMove->getColor())
		return false;
	else
	{	
		// store piece being capture for possible reversing of the move
		Piece* temp = squares[to.row][to.col];

		// Logic for capture
		if(squares[to.row][to.col])
		{
			// Remove piece from active list
			if (squares[to.row][to.col]->getColor() == WHITE)
			{
				for (int i = 0; i < 16; i++)
					if (squares[to.row][to.col] == activePieceWhite[i])
						activePieceWhite[i] = nullptr;
			}
			else if (squares[to.row][to.col]->getColor() == BLACK)
			{
				for (int i = 0; i < 16; i++)
					if (squares[to.row][to.col] == activePieceBlack[i])
						activePieceBlack[i] = nullptr;
			}
		}
		// logic for moving
		squares[to.row][to.col] = toMove;
		squares[from.row][from.col] = nullptr;

		// if move leads to check reverse it and return false
		if (computeCheck(toMove->getColor()))
		{
			squares[from.row][from.col] = toMove;
			squares[to.row][to.col] = temp;
			return false;
		}
		else
		{
			// Deallocate Captured piece in case of No reverse
			delete temp;
		}
		
	}

	return true;
}

bool Board::isUnderAttack(Position pos, Color byColor) const
{
	Position piecePos;
	if (byColor == BLACK)
		for (int i = 0; i < 16; i++)
		{
			if (!activePieceBlack[i])
				continue;
			piecePos = GetPiecePosition(activePieceBlack[i]);
			if (activePieceBlack[i]->isValidMove(piecePos, pos, *this))
				return true;
		}
	else if (byColor == WHITE)
		for (int i = 0; i < 16; i++)
		{
			if (!activePieceWhite[i])
				continue;
			piecePos = GetPiecePosition(activePieceWhite[i]);
			if (activePieceWhite[i]->isValidMove(piecePos, pos, *this))
				return true;
		}

	return false;
}

bool Board::computeCheck(Color on) const
{
	if (on == WHITE)
	{
		Piece* king = activePieceWhite[4]; // get King
		if (!king)
			return false;
		isUnderAttack(GetPiecePosition(king), BLACK);
	}
	else if (on == BLACK)
	{
		Piece* king = activePieceBlack[4]; // get King
		if (!king)
			return false;
		isUnderAttack(GetPiecePosition(king), WHITE);
	}
}

Piece* Board::getPiece(Position at) const 
{ 
	return squares[at.row][at.col]; 
}

Board::~Board()
{
	// Free Dynamically Allocated Memory for Pieces in the Board
	for (int i = 0; i < 1; i++)
		for (int j = 0; j < 8; j++)
			if (squares[i][j])
				delete (squares[i][j]);
}
