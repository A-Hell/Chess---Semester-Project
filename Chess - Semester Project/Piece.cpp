/*
* Last Edited:  5/7/2026
* Author:       Amna Akbar
* Description:
*		Implemented: Movement logic for all piece classes
		Pawn: did not implement en' pasant. Pawn can move 2 squares forward on first move, 1 forward in normal moves and 1 in diagonal when capturing
		Rook: Moves vertical and horizontal within the same row / col
		Knight: Moves in an L-shape, does not need to detect obstacle in path
		Bishop: Moves diagnonally where distance from the start position to end position is same in rows and columns
		Queen: Combined Rook and Bishop Movement
		King : Can move one square in any direction
		For Queen, Bishop, Rook and Pawn path blocking was also implemented where encessary
*/

#include "Piece.h"
#include "Board.h"

//PIECE CLASS
Piece::Piece()              //Brief Default Constructor
{                           //Initializes a piece to an empty state with no color and no type
	colour = NONE;
	piece = EMPTY;
}
Piece::Piece(Color colour, PieceType piece) : colour(colour), piece(piece)
{
	//Parametrized Constructor 
	//Parameter Colour The side piece belongs to (WHITE/BLACK) 
	//Parameter PieceType The specific type of the piece (e.g PAWN,KING) 
}
Color Piece::getColor() const
{                                  //Gets the Colour of piece
	return colour;                //Return Colour enum value(WHITE, BLACK, or NONE)
}
PieceType Piece::getType() const
{                                  //Gets the type of the piece.
	return piece;                  //return PieceType enum value
}

Piece::~Piece()
{
	/*
	* Virtual Destructor
	* Ensures derived classes are cleaned up properly when deleted via a base pointer.
	*/
}
// PAWN CLASS
Pawn::Pawn()
{
	//Default Constructor
	//Creates a default Pawn piece. Calls the base Piece constructor  to initialize with default values
}
Pawn::Pawn(Color colour) : Piece(colour, PAWN)    //Parameterized Constructor
{                           //Initializes a Pawn with a specific color and sets its type to PAWN
							//Parameter colour The color assigned to this pawn(WHITE or BLACK).
}
char Pawn::getSymbol() const             //Returns the character representation of the Pawn.
{                             //Returns an uppercase 'P' for White pieces and a lowercase 'p' 
	char Symbol = 'P';        //for Black pieces to follow standard algebraic notation.
	return (colour == WHITE) ? Symbol : tolower(Symbol);
}

bool Pawn::isValidMove(Position from, Position to, const Board& board) const
{
	int rowDis = to.row - from.row;
	int colDis = abs(to.col - from.col);

	// check vertical limit
	if (colDis > 1)
		return false;

	// check if there is a piece in from of the pawn
	if (board.getPiece(to) && colDis == 0)
		return false;

	if (colour == BLACK)
	{
		// check if move is forward
		if (rowDis < 1)
			return false;

		// check length of forward movement, 2 if first move, 1 otherwise
		if (from.row == 1)
		{
			if (rowDis <= 2 && colDis == 0)
			{
				for (int i = from.row + 1; i < to.row; i++)
					if (board.getPiece(Position{ i, from.col }))
						return false;
				return true;
			}
			else if (rowDis > 1)
				return false;
		}
		else if (rowDis > 1)
			return false;
	}

	if (colour == WHITE)
	{
		if (rowDis > -1)
			return false;

		if (colDis > 1)
			return false;

		// check length of forward movement, 2 if first move, 1 otherwise
		if (from.row == 6)
		{
			if (rowDis >= -2 && colDis == 0)
			{
				for (int i = from.row - 1; i > to.row; i--)
					if (board.getPiece(Position{ i, from.col }))
						return false;
				return true;
			}
			else if (rowDis < -1)
				return false;
		}
		if (rowDis < -1) // can't move more than one square if colDis not 0
			return false;
	}

	// Diagonal Check for capture
	if (!board.getPiece(to) && colDis == 1)
		return false;

	return true;
}

//ROOK CLASS
Rook::Rook()
{
	//Default Constructor
	//Creates a default Rook piece. Calls the base Piece constructor to initialize with default values
}
Rook::Rook(Color colour) :Piece(colour, ROOK)   //Parameterized Constructor
{    //Initializes a ROOK with a specific color and sets its type to ROOK
	//Parameter colour The color assigned to this Rook(WHITE or BLACK).
}
char Rook::getSymbol() const   //Returns the character representation of the Rook.
{                             //Returns an uppercase 'R' for White pieces and a lowercase 'r'
	char Symbol = 'R';        //for Black pieces to follow standard algebraic notation.
	return (colour == WHITE) ? Symbol : tolower(Symbol);
}
bool Rook::isValidMove(Position from, Position to, const Board& board) const
{
	// if not Vertical of Horizontal return false
	if (from.row != to.row || from.col != to.col)
		return false;

	// Check Obstacles in horizaontal and vertical path
	int rowDis = to.row - from.row;
	int colDis = to.col - from.col;

	if (rowDis > 0) // check direction of movement
	{
		// move down the board
		for (int i = from.row + 1; i < to.row; i++)
			if (board.getPiece(Position{ i, from.col }))
				return false;
	}
	else if (rowDis < 0)
	{
		// move up the board
		for (int i = from.row - 1; i > to.row; i--)
			if (board.getPiece(Position{ i, from.col }))
				return false;
	}
	else if (colDis > 0)
	{
		// move right
		for (int i = from.col + 1; i < to.col; i++)
			if (board.getPiece(Position{ from.row, i }))
				return false;
	}
	else if (colDis < 0)
	{
		// move left
		for (int i = from.col - 1; i > to.col; i--)
			if (board.getPiece(Position{ from.row, i }))
				return false;
	}

	return true;
}

//KNIGHT CLASS
Knight::Knight()
{
	//Default Constructor
	//Creates a default Knight piece. Calls the base Piece constructor to initialize with default values
}
Knight::Knight(Color colour) :Piece(colour, KNIGHT)      //Parameterized Constructor
{  //Initializes a Knight with a specific color and sets its type to Knight
	//Parameter colour The color assigned to this Knight(WHITE or BLACK).

}
char Knight::getSymbol() const     //Returns the character representation of the Knight.
{                                  //Returns an uppercase 'N' for White pieces and a lowercase 'n'
	char Symbol = 'N';              //for Black pieces to follow standard algebraic notation.
	return (colour == WHITE) ? Symbol : tolower(Symbol);
}

bool Knight::isValidMove(Position from, Position to, const Board& board) const
{

	int rowDis = abs(to.row - from.row);
	int colDis = abs(to.col - from.col);

	// Distance must be of 2 units in one direction and of 1 unit in the other direction
	if ((rowDis == 2 && colDis == 1) || (rowDis == 1 && colDis == 2))
		return true;
	return false;
}

//BISHOP CLASS
Bishop::Bishop()
{
	//Default Constructor
	//Creates a default Bishop piece. Calls the base Piece constructor to initialize with default values
}
Bishop::Bishop(Color colour) :Piece(colour, BISHOP)    //Parameterized Constructor
{    //Initializes a Bishop with a specific color and sets its type to Bishop
	//Parameter colour The color assigned to this Bishop(WHITE or BLACK).

}

char Bishop::getSymbol() const                  //Returns the character representation of the Bishop.
{                                                //Returns an uppercase 'B' for White pieces and a lowercase 'b'
	char Symbol = 'B';                           //for Black pieces to follow standard algebraic notation.
	return (colour == WHITE) ? Symbol : tolower(Symbol);
}

bool Bishop::isValidMove(Position from, Position to, const Board& board) const
{

	int rowDis = to.row - from.row;
	int colDis = to.col - from.col;

	// Check if move is diagonal
	if (abs(rowDis) != abs(colDis))
		return false;

	// Check for obstacles in the diagonal path
	if (rowDis > 0 && colDis > 0)
	{
		for (int i = from.row + 1, j = from.col + 1; i < to.row && j < to.col; i++)
		{
			if (board.getPiece(Position{ i, j }))
				return false;
			j++;
		}
	}
	else if (rowDis > 0 && colDis < 0)
	{
		for (int i = from.row + 1, j = from.col - 1; i < to.row && j > to.col; i++)
		{
			if (board.getPiece(Position{ i, j }))
				return false;
			j--;
		}
	}
	else if (rowDis < 0 && colDis < 0)
	{
		for (int i = from.row - 1, j = from.col - 1; i > to.row && j > to.col; i--)
		{
			if (board.getPiece(Position{ i, j }))
				return false;
			j--;
		}
	}
	else if (rowDis < 0 && colDis > 0)
	{
		for (int i = from.row - 1, j = from.col + 1; i > to.row && j < to.col; i--)
		{
			if (board.getPiece(Position{ i, j }))
				return false;
			j++;
		}
	}

	return true;
}

//Queen Class
Queen::Queen()
{
	//Default Constructor
   //Creates a default Queen piece. Calls the base Piece constructor to initialize with default values
}
Queen::Queen(Color colour) :Piece(colour, QUEEN)       //Parameterized Constructor
{  //Initializes a Queen with a specific color and sets its type to Queen
	//Parameter colour The color assigned to this Queen(WHITE or BLACK).
}
char Queen::getSymbol() const         //Returns the character representation of the Queen.
{                                     //Returns an uppercase 'Q' for White pieces and a lowercase 'q'
	char Symbol = 'Q';                 //for Black pieces to follow standard algebraic notation.
	return (colour == WHITE) ? Symbol : tolower(Symbol);
}

bool Queen::isValidMove(Position from, Position to, const Board& board) const
{

	// Combines the diagonal movement logic of the Bishop with Rook

	int rowDis = to.row - from.row;
	int colDis = to.col - from.col;

	bool straightMove = (from.row == to.row || from.col == to.col);
	bool diagonalMove = (abs(rowDis) == abs(colDis));

	// check if move is either straight or diagonal, if not return false
	if (!straightMove && !diagonalMove)
		return false;

	if (straightMove)
	{
		// Check for obstacles in the horizontal and vertical path
		if (rowDis > 0) // check direction of movement
		{
			// move down the board
			for (int i = from.row + 1; i < to.row; i++)
				if (board.getPiece(Position{ i, from.col }))
					return false;
		}
		else if (rowDis < 0)
		{
			// move up the board
			for (int i = from.row - 1; i > to.row; i--)
				if (board.getPiece(Position{ i, from.col }))
					return false;
		}
		else if (colDis > 0)
		{
			// move right
			for (int i = from.col + 1; i < to.col; i++)
				if (board.getPiece(Position{ from.row, i }))
					return false;
		}
		else if (colDis < 0)
		{
			// move left
			for (int i = from.col - 1; i > to.col; i--)
				if (board.getPiece(Position{ from.row, i }))
					return false;
		}
	}

	// Check for obstacles in the diagonal path
	if (diagonalMove)
	{
		if (rowDis > 0 && colDis > 0)
		{
			for (int i = from.row + 1, j = from.col + 1; i < to.row && j < to.col; i++)
			{
				if (board.getPiece(Position{ i, j }))
					return false;
				j++;
			}
		}

		else if (rowDis > 0 && colDis < 0)
		{
			for (int i = from.row + 1, j = from.col - 1; i < to.row && j > to.col; i++)
			{
				if (board.getPiece(Position{ i, j }))
					return false;
				j--;
			}
		}
		else if (rowDis < 0 && colDis < 0)
		{
			for (int i = from.row - 1, j = from.col - 1; i > to.row && j > to.col; i--)
			{
				if (board.getPiece(Position{ i, j }))
					return false;
				j--;
			}
		}
		else if (rowDis < 0 && colDis > 0)
		{
			for (int i = from.row - 1, j = from.col + 1; i > to.row && j < to.col; i--)
			{
				if (board.getPiece(Position{ i, j }))
					return false;
				j++;
			}
		}
	}

bool Queen::isValidMove(Position from, Position to, const Board& board) const
{

	// Combines the diagonal movement logic of the Bishop with Rook

	int rowDis = to.row - from.row;
	int colDis = to.col - from.col;

	bool straightMove = (from.row == to.row || from.col == to.col);
	bool diagonalMove = (abs(rowDis) == abs(colDis));

	// check if move is either straight or diagonal, if not return false
	if (!straightMove && !diagonalMove)
		return false;

	if (straightMove)
	{
		// Check for obstacles in the horizontal and vertical path
		if (rowDis > 0) // check direction of movement
		{
			// move down the board
			for (int i = from.row + 1; i < to.row; i++)
				if (board.getPiece(Position{ i, from.col }))
					return false;
		}
		else if (rowDis < 0)
		{
			// move up the board
			for (int i = from.row - 1; i > to.row; i--)
				if (board.getPiece(Position{ i, from.col }))
					return false;
		}
		else if (colDis > 0)
		{
			// move right
			for (int i = from.col + 1; i < to.col; i++)
				if (board.getPiece(Position{ from.row, i }))
					return false;
		}
		else if (colDis < 0)
		{
			// move left
			for (int i = from.col - 1; i > to.col; i--)
				if (board.getPiece(Position{ from.row, i }))
					return false;
		}
	}

	// Check for obstacles in the diagonal path
	if (diagonalMove)
	{
		if (rowDis > 0 && colDis > 0)
		{
			for (int i = from.row + 1, j = from.col + 1; i < to.row && j < to.col; i++)
			{
				if (board.getPiece(Position{ i, j }))
					return false;
				j++;
			}
		}

		else if (rowDis > 0 && colDis < 0)
		{
			for (int i = from.row + 1, j = from.col - 1; i < to.row && j > to.col; i++)
			{
				if (board.getPiece(Position{ i, j }))
					return false;
				j--;
			}
		}
		else if (rowDis < 0 && colDis < 0)
		{
			for (int i = from.row - 1, j = from.col - 1; i > to.row && j > to.col; i--)
			{
				if (board.getPiece(Position{ i, j }))
					return false;
				j--;
			}
		}
		else if (rowDis < 0 && colDis > 0)
		{
			for (int i = from.row - 1, j = from.col + 1; i > to.row && j < to.col; i--)
			{
				if (board.getPiece(Position{ i, j }))
					return false;
				j++;
			}
		}
	}

	return true;
}

//KING CLASS
//Default Constructor
//Creates a default King piece. Calls the base Piece constructor to initialize with default values
King::King()
{

}

//Parameterized Constructor
//Initializes a King with a specific color and sets its type to King
//Parameter colour The color assigned to this King(WHITE or BLACK).
King::King(Color colour) :Piece(colour, KING)
{

}
char King::getSymbol() const       //Returns the character representation of the King.
{                                   //Returns an uppercase 'K' for White pieces and a lowercase 'k'
	char Symbol = 'K';               //for Black pieces to follow standard algebraic notation.
	return (colour == WHITE) ? Symbol : tolower(Symbol);
}

bool King::isValidMove(Position from, Position to, const Board& board) const
{
	int rowDis = abs(to.row - from.row);
	int colDis = abs(to.col - from.col);
	
	if (rowDis > 1 || colDis > 1)
		return false;

	return true;
}

bool King::isValidMove(Position from, Position to, const Board& board) const
{
	int rowDis = abs(to.row - from.row);
	int colDis = abs(to.col - from.col);
	
	if (rowDis > 1 || colDis > 1)
		return false;

	return true;
}

bool King::isValidMove(Position from, Position to, const Board& board) const
{
	int rowDis = abs(to.row - from.row);
	int colDis = abs(to.col - from.col);

	if (rowDis > 1 || colDis > 1)
		return false;

	return true;
}