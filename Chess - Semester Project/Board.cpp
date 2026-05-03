/*
* Last Edited: 5/2/26
* Author: Armaghan
* Description:
	Initialized the Pieces with Colors and Types.
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

void Board::movePiece(Position from, Position to)
{
	// Block Invalid Indexes
	if (from.row < 0 || from.row > 7 || from.col < 0 || from.col > 7 ||
		to.row < 0 || to.row > 7 || to.col < 0 || to.col > 7)
		return;
	// Block Null Piece
	if (!squares[from.row][from.col])
		return;

	Piece* toMove = squares[from.row][from.col];
	squares[to.row][to.col] = toMove;
	squares[from.row][to.row] = nullptr;
}

Board::~Board()
{
	for (int i = 0; i < 1; i++)
		for (int j = 0; j < 8; j++)
			if (squares[i][j])
				delete (squares[i][j]);
}
