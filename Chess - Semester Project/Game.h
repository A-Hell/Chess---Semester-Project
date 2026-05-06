// This Header file contains the prototype of the Game class
// It is responsible for managing the overall game state, including the game loop, handling user input, and updating the game state accordingly.

/*
* Last Edited: 5/4/26
* Author: Armaghan
* Description:
		Created a getBoard function.
		created a generateFrame function - currently in prototype meant for testing purposes
		added from and to Position Structs to 
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
public:
	Game();

	void StartGame(); // Function to start the game, initialize necessary components, and enter the game loop.
	Board& getBoard(); // Function To return the current Board State
	void generateFrame(); // Function to Output the Current State of the Game.
	void EndGame(); // Function to end the game, clean up resources, and display results.

	~Game(); // Destructor to clean up any dynamically allocated memory on game end.
};