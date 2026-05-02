/*
* Last Edited: 5/2/26
* Author: Armaghan
* Description:
	Implemented the following functions of the Board Class:
	- Board() : Initializes the chessboard and sets up pieces.
	- GetPiecePosition(Piece* piece) : Returns the position of a given piece.
	- setPiecePosition(Piece* piece, Position pos) : Sets the position of a given piece on the board.
	- movePiece(Position from, Position to) : Moves a piece from one position to another
	- ~Board() : Cleans up any dynamically allocated memory on game.
*/

#include "Board.h"


// Default Constructor
Board::Board()
{
	// Set the board on default Settings
	
	// Set Up White
	squares[0][0] = new Rook();
	squares[0][1] = new Knight();
	squares[0][2] = new Bishop();
	squares[0][3] = new Queen();
	squares[0][4] = new King();
	squares[0][5] = new Bishop();
	squares[0][6] = new Knight();
	squares[0][7] = new Rook();
	for (int i = 0; i < 8; i++)
	squares[1][i] = new Pawn();

	// Set Up White
	squares[7][0] = new Rook();
	squares[7][1] = new Knight();
	squares[7][2] = new Bishop();
	squares[7][3] = new Queen();
	squares[7][4] = new King();
	squares[7][5] = new Bishop();
	squares[7][6] = new Knight();
	squares[7][7] = new Rook();
	for (int i = 0; i < 8; i++)
	squares[6][i] = new Pawn();

	// Set the Rest of the board as Empty
	for (int i = 2; i < 6; i++)
		for (int j = 0; j < 8; j++)
			squares[i][j] = nullptr;

}

Position Board::GetPiecePosition(Piece* piece)
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
