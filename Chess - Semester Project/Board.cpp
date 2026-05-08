/*
* Last Edited: 5/8/26
* Author: Amna
* Description:
*		Modified: movePiece to handle "Double Move" logic for Castling (automatically repositioning the Rook).
*		Modified: movePiece to detect Pawn Promotion and trigger the replacement of Pawn objects.
*		Implemented: promotePawn helper function to safely deallocate pawns and update active piece pointers to new Queens.
*		Implemented: setMovedStatus and getMovedStatus calls to ensure King and Rook cannot castle after their first move.
*/

#include "Board.h"
#include "Interface.h"

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
	if (pos.row < 0 || pos.row > 7 || pos.col < 0 || pos.col > 7 || !piece)
		return;

	squares[pos.row][pos.col] = piece;
}

void Board::setupCastlingTest()
{
	// Clear the board and delete existing pieces
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			delete squares[i][j];
			squares[i][j] = nullptr;
		}

	// Clear active piece lists
	for (int i = 0; i < 16; i++)
	{
		activePieceWhite[i] = nullptr;
		activePieceBlack[i] = nullptr;
	}

	whiteKing = nullptr;
	blackKing = nullptr;

	// Setup White Castling (Kingside and Queenside)
	squares[7][4] = new King(WHITE);
	whiteKing = squares[7][4];
	squares[7][0] = new Rook(WHITE);
	squares[7][7] = new Rook(WHITE);
	squares[6][7] = new Pawn(WHITE);

	// Setup Black Castling (Kingside and Queenside)
	squares[0][4] = new King(BLACK);
	blackKing = squares[0][4];
	squares[0][0] = new Rook(BLACK);
	squares[0][7] = new Rook(BLACK);

	// Add an enemy piece to test "Castling through check"
	squares[1][3] = new Rook(BLACK);

	// Rebuild active piece arrays for accurate attack detection
	activePieceWhite[0] = squares[7][0];
	activePieceWhite[1] = squares[7][4];
	activePieceWhite[2] = squares[7][7];
	activePieceWhite[3] = squares[6][7];

	activePieceBlack[0] = squares[0][0];
	activePieceBlack[1] = squares[0][4];
	activePieceBlack[2] = squares[0][7];
	activePieceBlack[3] = squares[1][3];
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
		// --- CASTLING ROOK REPOSITIONING ---
		// If a King moved 2 squares, we must move the Rook as well
		if (toMove->getType() == KING && abs(to.col - from.col) == 2)
		{
			int rookOldCol = (to.col > from.col) ? 7 : 0;
			int rookNewCol = (to.col > from.col) ? 5 : 3;

			Piece* castlingRook = squares[from.row][rookOldCol];
			squares[from.row][rookNewCol] = castlingRook;
			squares[from.row][rookOldCol] = nullptr;

			// Mark the Rook as moved
			static_cast<Rook*>(castlingRook)->setMovedStatus(true);
		}

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

		// Safely checks whether the moved piece is a King.
        // dynamic_cast returns nullptr if the piece is not actually a King.
		King* king = dynamic_cast<King*>(toMove);
		if (king)
		{
			king->setMovedStatus(true);
		}

		// Safely checks whether the moved piece is a Rook.
        // dynamic_cast returns nullptr if the piece is not actually a Rook.
		Rook* rook = dynamic_cast<Rook*>(toMove);
		if (rook)
		{
			rook->setMovedStatus(true);
		}
		
	}
	// --- PAWN PROMOTION DETECTION ---
	Pawn* pawn = dynamic_cast<Pawn*>(toMove);
	if (pawn && !ghost)
	{
		// White promotes at the top (row 0), Black at the bottom (row 7)
		bool whitePromotion = (pawn->getColor() == WHITE && to.row == 0);
		bool blackPromotion = (pawn->getColor() == BLACK && to.row == 7);

		if (whitePromotion || blackPromotion)
		{
			PieceType promotionChoice = Interface::getPromotionInput();
			promotePawn(to, promotionChoice);
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

void Board::promotePawn(Position position, PieceType promotionType)
{
	// 1. Get the pawn currently at the promotion square
	Piece* oldPawn = squares[position.row][position.col];
	if (!oldPawn || oldPawn->getType() != PAWN)
		return;

	Color pawnColor = oldPawn->getColor();
	Piece* promotedPiece = nullptr;

	// 2. Create the new piece object based on the user's choice
	switch (promotionType)
	{
	case QUEEN:
	{
		promotedPiece = new Queen(pawnColor);
		break;
	}
	case ROOK:
	{
		promotedPiece = new Rook(pawnColor);
		break;
	}
	case BISHOP:
	{
		promotedPiece = new Bishop(pawnColor);
		break;
	}
	case KNIGHT:
	{
		promotedPiece = new Knight(pawnColor);
		break;
	}
	default:
	{
		promotedPiece = new Queen(pawnColor);
		break;
	}

	}

	// 3. Update the Active Piece Array
	Piece** activePieces = (pawnColor == WHITE) ? activePieceWhite : activePieceBlack;

	for (int i = 0; i < 16; i++)
	{
		if (activePieces[i] == oldPawn)
		{
			activePieces[i] = promotedPiece;
			break;
		}
	}

	// 4. Update the Board
	delete oldPawn;
	squares[position.row][position.col] = promotedPiece;

}

Piece* Board::getPiece(Position at) const 
{ 
	return squares[at.row][at.col]; 
}

Board::~Board()
{
	// Free Dynamically Allocated Memory for Pieces in the Board
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if (squares[i][j])
				delete (squares[i][j]);
}
