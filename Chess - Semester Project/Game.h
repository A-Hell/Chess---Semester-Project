// This Header file contains the prototype of the Game class
// It is responsible for managing the overall game state, including the game loop, handling user input, and updating the game state accordingly.

/*
* Last Edited: 5/2/26
* Author: Armaghan
* Description:
		Created the Game class and its member functions.
		Added and Implemented the following functions:
		- Game() : Initializes the game state and sets up necessary components.
		- StartGame() : Function to start the game, initialize necessary components, and enter the game loop.
		- EndGame() : Function to end the game, clean up resources, and display results.
		- ~Game() : Destructor to clean up any dynamically allocated memory on game end.
*/

#pragma once
#include "Common.h"
#include "Board.h"

class Game
{
	Board* board;
public:
	Game();

	void StartGame(); // Function to start the game, initialize necessary components, and enter the game loop.
	void EndGame(); // Function to end the game, clean up resources, and display results.

	~Game(); // Destructor to clean up any dynamically allocated memory on game end.
};