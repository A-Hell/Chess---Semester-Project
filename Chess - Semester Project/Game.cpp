
/*
* Last Edited: 5/6/26
* Author: Armaghan
* Description:
*		Implemented genreateFrame and getBoard functions.
*		updated StartGame to initialize the game state and call generateFrame to start the game loop.
*		updated generateFrame logic to validate moves.
*/

#include "Game.h"

Game::Game()
{
	// Initialize the game state
	this->board = nullptr;
	from = { -1,-1 };
	to = { -1,-1 };
	currentPlayer = WHITE;
}

void Game::StartGame()
{
	this->board = new Board;
	from = { -1,-1 };
	to = { -1,-1 };
	currentPlayer = WHITE;
	generateFrame();
}

Board& Game::getBoard()
{
	return *board;
}

void Game::generateFrame()
{
	while (true)
	{
		system("cls");

		// Get input once
		interface.renderBoard(*board);
		interface.getMoveInput(from, to);

		// Keep asking for input until a valid move is made
		while (!board->movePiece(from, to))
		{
			interface.renderBoard(*board);
			cout << "Invalid Move! Please try again." << endl;
			interface.getMoveInput(from, to);
		}

		system("pause");
	}

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