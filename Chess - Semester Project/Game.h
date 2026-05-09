// This Header file contains the prototype of the Game class
// It is responsible for managing the overall game state, including the game loop, handling user input, and updating the game state accordingly.

/*
* Last Edited: 5/8/26
* Author: Rayyan
* Description:
*		Added: moveHistory[][] to store previous moves
*		Added: StoreMoveHistory to store the moves in the correct order
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
	Position moveHistory[100][2];
public:
	Game();

	void StartGame(); // Function to start the game, initialize necessary components, and enter the game loop.
	Board& getBoard(); // Function To return the current Board State
	void gameLoop(); // Function to manage the main game loop.
	void generateFrame(bool invalidMove = false); // Function to render the current state of the game.
	void changeTurn(); // Function to swap Current Player
	bool validatePiece(Position at); // Function to validate that piece is being moved by the correct player
	bool processTurn(); // Function to call the necessary Game checks to make sure the Turn was successful and piece was moved
	bool getCheckStatus() const; // Returns wether the current player is in check or not
	void storeMoveHistory(Position from, Position to); // Function to store the history of moves 
	void EndGame(); // Function to end the game, clean up resources, and display results.

	~Game(); // Destructor to clean up any dynamically allocated memory on game end.
};