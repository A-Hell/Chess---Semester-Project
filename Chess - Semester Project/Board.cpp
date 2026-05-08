/*
* Last Edited: 5/8/26
* Author: Armaghan
* Description:
*		Implemented: lookForMoves function to loop through all pieces of a specific color and check if they have any valid moves left, used for checkmate and stalemate detection
*		Implemented: ghost parameter to movePiece function to allow for checking valid moves without actually moving the piece
*		Fixed: A critical Bug in computeCheck where it wasn't returning true when king was under attack
*		Modified: isUnderAttack and lookForMoves to reduce line of codes by implementing the same logic in both functions in one loop and just changing the return value based on the function
*		Modified: Capture Cleanup to clean up Active Piece array properly and to only delete the piece when the move is not reversed
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
	blackKing = squares[0][4];


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
	whiteKing = squares[7][4];

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

bool Board::movePiece(Position from, Position to, bool ghost )
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

		// logic for moving / capture
		squares[to.row][to.col] = toMove;
		squares[from.row][from.col] = nullptr;

		// if move leads to check reverse it and return false
		if (computeCheck(toMove->getColor()))
		{
			squares[from.row][from.col] = toMove;
			squares[to.row][to.col] = temp;
			return false;
		}
		else if (ghost)
		{
			// ghost case to check for valid moves without actually moving
			squares[from.row][from.col] = toMove;
			squares[to.row][to.col] = temp;
		}
		else
		{
			// Deallocate Captured piece in case of No reverse
			if (temp)
			{
				// Remove piece from active list
				Piece**  activePieces = (temp->getColor() == BLACK) ? activePieceBlack : activePieceWhite;
				for (int i = 0; i < 16; i++)
					if (temp == activePieces[i])
						activePieces[i] = nullptr;
			}
			delete temp;
		}
		
	}

	return true;
}

bool Board::isUnderAttack(Position pos, Color byColor) const
{
	Piece* const* activePieces = (byColor == BLACK) ? activePieceBlack : activePieceWhite;

	for (int i = 0; i < 16; i++)
	{
		if (!activePieces[i])
			continue;

		Position piecePos = GetPiecePosition(activePieces[i]);
		if (activePieces[i]->isValidMove(piecePos, pos, *this))
			return true;
	}

	return false;
}

bool Board::computeCheck(Color on) const
{
	if (on == WHITE)
	{
		if (!whiteKing)
			return false;
		if (isUnderAttack(GetPiecePosition(whiteKing), BLACK))
			return true;
	}
	else if (on == BLACK)
	{
		if(!blackKing)
			return false;
		if (isUnderAttack(GetPiecePosition(blackKing), WHITE))
			return true;
	}
	return false;
}

bool Board::lookForMoves(Color on)
{
	bool moveAvailiable = true;
	Piece* const* activePieces = (on == BLACK) ? activePieceBlack : activePieceWhite;

	for (int a = 0; a < 16; a++)
	{
		Piece* current = activePieces[a];
		if (current)
		{
			Position from = GetPiecePosition(current);
			for (int i = 0; i < 8; i++)
				for (int j = 0; j < 8; j++)
					if (movePiece(from, Position{ i,j }, true)) // use ghost move
						return true; // if valid move found no checkamte or stalemate
		}

	}
	return false;
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
