
/*
* Last Edited: 5/2/26
* Author: Armaghan
* Description:
		Implemented the following functions of the Game Class:
		- Game() : Initializes the game state and starts with no board.
		- StartGame() : Function to start the game and initialize the board.
		- EndGame() : Function to end the game, clean up resources, and display results. Works with StartGame() to manage the GameCycle.
		- ~Game() : Destructor to clean up any dynamically allocated memory on game end.
*/


#include "Game.h"

Game::Game()
{
	this->board = nullptr;
}

void Game::StartGame()
{
	this->board = new Board;
}

void Game::EndGame()
{
	delete this->board;
	this->board = nullptr;
}

Game::~Game()
{
	if (this->board)
		delete this->board;
}