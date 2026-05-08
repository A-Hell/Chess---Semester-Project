// This Header file contains the prototype of the Game class
// It is responsible for managing the overall game state, including the game loop, handling user input, and updating the game state accordingly.

/*
* Last Edited: 5/6/26
* Author: Armaghan
* Description:
		Added Change Turn Function to swap the current player
		Added Validate Piece function to make sure player moves only their pieces
		Added processTurn function as a master check, to simplify the check logic in generateFrame and make code more readeable
				it is also now responsible for moving the piece.
*/

#pragma once
#include "Common.h"
#include "Board.h"
#include "Interface.h"

class Game
{
	Board* board;
	Interface interface;
	Position from;
	Position to;
	Color currentPlayer; 
	bool inCheck;
	bool Checkmate;
	bool Stalemate;
public:
	Game();

	void StartGame(); // Function to start the game, initialize necessary components, and enter the game loop.
	Board& getBoard(); // Function To return the current Board State
	void generateFrame(); // Function to Output the Current State of the Game.
	void changeTurn(); // Function to swap Current Player
	bool validatePiece(Position at); // Function to validate that piece is being moved by the correct player
	bool processTurn(); // Function to call the necessary Game checks to make sure the Turn was successful and piece was moved
	bool getCheckStatus(); // Returns wether the current player is in check or not
	void EndGame(); // Function to end the game, clean up resources, and display results.

	~Game(); // Destructor to clean up any dynamically allocated memory on game end.
};