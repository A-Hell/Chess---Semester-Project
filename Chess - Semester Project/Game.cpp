
/*
* Last Edited: 5/6/26
* Author: Armaghan
* Description:
*		Implemented the following functions of the Game class:
* 			validatePiece(Position at) : Checks if the piece at the given position belongs to the current player, returns true if valid, false otherwise.
*			processTurn() : Validates the move and moves the piece if valid, returns true if successful, false otherwise.
* 			changeTurn() : Swaps the current player after a successful move.
* 
*		Modified generateFrame() to call processTurn and changeTurn to simplify the game loop and make moved piece validate with the player
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
		interface.renderCurrentPlayer(currentPlayer);
		interface.getMoveInput(from, to);

		// Keep asking for input until a valid move is made
		while (!processTurn())
		{
			system("cls");

			interface.renderBoard(*board);
			interface.renderCurrentPlayer(currentPlayer);
			cout << RED << "Invalid Move! Please try again." << RESET << endl;

			interface.getMoveInput(from, to);
		}

		system("pause");
		changeTurn(); // change turn after a successful loop
	}

}

bool Game::processTurn()
{
	if (!validatePiece(from))
	{
		cout << RED << "You must move your own piece!" << RESET << endl;
		return false;
	}

	if (!board->movePiece(from, to))
		return false;

	return true;
}

void Game::changeTurn() { currentPlayer = ((currentPlayer == WHITE) ? BLACK : WHITE); }

bool Game::validatePiece(Position at)
{
	// if piece of the color being moved is the same as the player return true
	if (board->getPiece(at))
		if (board->getPiece(at)->getColor() == currentPlayer)
		return true;
	else
		return false;
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