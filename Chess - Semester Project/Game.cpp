
/*
* Last Edited: 5/8/26
* Author: Rayyan
* Description:
*		Renamed : generateFrame to gameLoop and made it responsible for the entire game loop, to simplify the code and make it more readeable
*		Modified: generateFrame now a diffrent function responsible for rendering the current state of the game, to simplify the game loop and make code more readeable
*/

#include "Game.h"

Game::Game()
{
	// Initialize the game state
	this->board = nullptr;
	from = { -1,-1 };
	to = { -1,-1 };
	currentPlayer = WHITE;
	inCheck = false;
	Checkmate = false;
	Stalemate = false;
}

void Game::StartGame()
{
	this->board = new Board;
	from = { -1,-1 };
	to = { -1,-1 };
	currentPlayer = WHITE;
	inCheck = false;
	Checkmate = false;
	Stalemate = false;
	gameLoop(); // Start the main game loop
}

Board& Game::getBoard()
{
	return *board;
}

void Game::gameLoop()
{
	while (true)
	{
		generateFrame();
		// Get input once
		interface.getMoveInput(from, to);

		// Keep asking for input until a valid move is made
		while (!processTurn())
		{
			generateFrame();
			cout << RED << "Invalid Move! Please try again." << RESET << endl;

			interface.getMoveInput(from, to);
		}

		// Break the Game loop when checkmate or stalemate
		if (Checkmate || Stalemate)
		{
			generateFrame();

			if (Checkmate)
				cout << endl << RED + "Checkmate Game over! " + RESET << ((currentPlayer == WHITE) ? (GRAY + "Black" + RESET) : (WHITE_ + "White" + RESET)) << RED + " Won " + RESET << endl;
			if (Stalemate)
				cout << endl << YELLOW + "Stalemate Game over! No Winners." + RESET << endl;
			break;
		}
		else
		{
			system("pause");
			changeTurn(); // change turn after a successful loop
		}
	}

}

void Game::generateFrame()
{
	system("cls");
	interface.renderHeader();
	interface.renderBoard(*board, inCheck);
	interface.renderCheckAlert(inCheck);
	interface.renderCurrentPlayer(currentPlayer);
}

bool Game::processTurn()
{
	if (!validatePiece(from))
	{
		cout << RED << "You must move your own piece!" << RESET << endl;
		return false;
	}

	// Block in valid move
	if (!board->movePiece(from, to))
		return false;

	// after Player makes a move check if other player is in check or not
	inCheck = board->computeCheck((currentPlayer == WHITE) ? BLACK : WHITE);

	// if in check and no moves availiable other player is in checkmate other if not in check but no availiable moves other player in stalemate
	if (inCheck)
	{
		if (!board->lookForMoves((currentPlayer == WHITE) ? BLACK : WHITE))
			Checkmate = true;
	}
	else
		if (!board->lookForMoves((currentPlayer == WHITE) ? BLACK : WHITE))
			Stalemate = true;

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

bool Game::getCheckStatus() const { return inCheck; }

void Game::EndGame()
{
	system("pause");
	delete this->board;
	this->board = nullptr;
}

Game::~Game()
{
	if (this->board)
		delete this->board;
}