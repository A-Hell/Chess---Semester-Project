
/*
* Last Edited: 5/8/26
* Author: Armaghan
* Description:
*		Modified: ProcessTurn to check fo check on opposite king after each move and to check for checkmate and stalemate conditions
*		Modified: generateFrame to break the game loop when checkmate or stalemate is detected and to display the appropriate end game message
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
	bool Checkmate = false;
	bool Stalemate = false;
}

void Game::StartGame()
{
	this->board = new Board;
	from = { -1,-1 };
	to = { -1,-1 };
	currentPlayer = WHITE;
	inCheck = false;
	bool Checkmate = false;
	bool Stalemate = false;
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

		// Break the Game loop when checkmate or stalemate
		if (Checkmate || Stalemate)
		{
			system("cls");
			interface.renderBoard(*board);
			if (Checkmate)
				cout << endl << RED + "Checkmate Game over!  " + RESET << ((currentPlayer == WHITE) ? "BLACK" : "WHITE") << RED + " Won " + RESET << endl;
			if (Stalemate)
				cout << endl << YELLOW + "Stalemate Game over!  " + RESET << ((currentPlayer == WHITE) ? "BLACK" : "WHITE") << YELLOW + " Won " + RESET << endl;
			break;
		}
		else
		{
			system("pause");
			changeTurn(); // change turn after a successful loop
		}
	}

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
	inCheck = board->computeCheck((currentPlayer == WHITE) ? BLACK : WHITE );

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

bool Game::getCheckStatus() { return inCheck; }

void Game::EndGame()
{
	cout << "\nGame Ended\n";
	system("pause");
	delete this->board;
	this->board = nullptr;
}

Game::~Game()
{
	if (this->board)
		delete this->board;
}