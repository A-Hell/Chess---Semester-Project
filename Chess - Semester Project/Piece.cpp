
/*
* Last Edited:  3/5/2026
* Author:       Amna Akbar
* Description:  This code establishes the Core Piece Hierarchy for a chess engine,
                focusing on the architectural setup required for Phase 1.
*/

#include "Piece.h"
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
bool Piece::isValidMove(Position from, Position to, const Board& board)
{
	/*
 * Validates movement logic for the piece.
 * note This is a placeholder for Phase 1. Currently allows all moves.
 * parameter from Starting coordinates
 * parameter to Destination coordinates
 * parameter board Reference to the current board state
 * return True if the move is legal, false otherwise.
 */
	return true;
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



